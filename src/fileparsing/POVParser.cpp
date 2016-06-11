//
// Created by lejonmcgowan on 4/10/16.
//

#include <fstream>
#include <cameras/PinholeCamera.h>
#include <geometry/Box.h>
#include <geometry/Sphere.h>
#include <geometry/Plane.h>
#include <geometry/Triangle.h>
#include <iostream>
#include <partitioning/Octree.h>
#include <cameras/scenes/OctreeScene.h>
#include <cameras/scenes/BVHScene.h>
#include "POVParser.h"

using namespace Eigen;
using namespace std;

//example parsing:  <1.33333, 0,  0>
Eigen::VectorXf POVParser::parseVector(std::string block, int size)
{
    //validation
    assert(block.front() == '<');
    if (block.back() != '>')
        block.pop_back();
    assert(block.back() == '>');

    VectorXf vec(size);
    int veciter = 0;
    std::string num;
    bool scanNumber = false;
    int numDecs = 0;
    int numNeg = 0;
    for(int i = 1; block[i] != '>'; i++)
    {
        if(block[i] == '.')
        {
            numDecs++;
            assert(numDecs == 1);
        }
        if (block[i] == '-')
        {
            numNeg++;
            assert(numNeg == 1);
        }
        if (block[i] == '.' || block[i] == '-' || isdigit(block[i]))
            scanNumber = true;

        if (block[i] == ',' || (block[i] == ' ' && scanNumber))
        {
            vec[veciter++] = stof(num);
            scanNumber = false;
            num.clear();
            if(numDecs > 0)
                numDecs--;
            if (numNeg > 0)
                numNeg--;

        }

        if(scanNumber)
            num += block[i];

    }
    //parseLastNum
    assert(scanNumber || veciter == size);
    if (scanNumber)
        vec[veciter++] = stof(num);
    return vec;
}

Eigen::Vector3f POVParser::parseMultVec(std::string parseNum)
{
    Vector3f vec;
    float num = 1;
    bool vecSet = false;
    bool divide = false;
    for (unsigned int i = 0; i < parseNum.length(); i++)
    {
        if(parseNum[i] == '<')
        {
            string vecstr;
            do
            {
                vecstr += parseNum[i];
            }while(parseNum[i++] != '>');
            vec = parseVector(vecstr);
            vecSet = true;
        }
        else if(parseNum[i] == 'x')
        {
            vec = Vector3f(1,0,0);
            vecSet = true;
        }
        else if(parseNum[i] == 'y')
        {
            vec = Vector3f(0,1,0);
            vecSet = true;
        }
        else if(parseNum[i] == 'z')
        {
            vec = Vector3f(0,0,1);
            vecSet = true;
        }
        else if(parseNum[i] == '.' || isdigit(parseNum[i]))
        {
            string numstr;
            do
            {
                numstr += parseNum[i];
            }while(parseNum[i] == '.' || isdigit(parseNum[i]));
            num = stof(numstr);
            if(divide)
                num = 1 / num;
        }
        else if(parseNum[i] == '/')
        {
            assert(vecSet); //ensure that this is is divided by a scalar, not vice versa
            divide = true;
        }
    }
    assert(vecSet);
    vec *= num;
    return vec;
}

/*
 example format:

 {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
 }
*/
shared_ptr<Camera> POVParser::parseCamera(std::string block)
{
    std::istringstream input(block);
    //cout << block << endl;

    std::string word;
    input >> word;
    assert(word == "{");

    Vector3f position,lookat,up, right, dummy;
    Vector3f* currentItem = &dummy;
    shared_ptr<PinholeCamera> camera;

    while(input >> word)
    {
        if(word == "location")
            currentItem = &position;
        else if(word == "up")
            currentItem = &up;
        else if(word == "right")
            currentItem = &right;
        else if(word == "look_at")
            currentItem = &lookat;
        else if(word.back() == 'x' || word.back() == 'y' || word.back() == 'z'
                || word.back() == '>' || isdigit(word.back()))
        {
            string numParse = word;
            *currentItem = parseMultVec(numParse);
        }
        else if(word.front() == '<')
        {
            string vecstr;
            vecstr += word;
            while(word.back() != '>')
            {
                input >> word;
                vecstr += word;
            }
           *currentItem = parseVector(vecstr);
        }
        else if(word.front() == '}')
            break;
        else
            cout << "WARNING: " << word << "is not a recognize keyword for camera. Discarding..." << endl;
    }
    camera.reset(new PinholeCamera(position,lookat,up));
    return camera;
}
/**
 * example input:
    {
        <-100, 100, 100> color rgb <1.5, 1.5, 1.5>
    }
 */
std::shared_ptr<Light> POVParser::parseLight(std::string block)
{
    std::istringstream input(block);
    //cout << block << endl;
    std::string word;
    input >> word;
    assert(word == "{");
    Vector3f location;
    Color color;
    //parse location
    string currentblock;
    while(currentblock.empty() || currentblock.back() != '>')
    {
        input >> word;
        currentblock += word;
    }
    location = parseVector(currentblock);
    //parse color

    //for now, will get full color support later
    input >> word;
    assert(word == "color");
    //make sure its rgb. light has no need for ft
    input >> word;
    assert(word == "rgb");

    //parse color
    currentblock.clear();
    while(currentblock.empty() || currentblock.back() != '>')
    {
        input >> word;
        currentblock += word;
    }
    Vector3f tmp;
    tmp = parseVector(currentblock);
    color.r = tmp[0];
    color.g = tmp[1];
    color.b = tmp[2];

    //todo make a parseLightModifiers(Light,block)
    return std::make_shared<Light>(location,color);
}

void POVParser::parseTransform(std::string block)
{
    std::istringstream input(block);
    std::string word;
    input >> word;
    assert(word == "{");
}
/**
 * box { <-2, -5, -5>, <2, 5, 5>
  pigment { color rgbf <1.0, 0.2, 1.0, 0.6>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.2 refraction 1.0 ior 1.9}
  rotate <0, -45, 0>
  translate <3, 0, -5>
}
 */
shared_ptr<Shape> POVParser::parseBox(std::string block)
{
    std::istringstream input(block);
    std::string word;
    input >> word;
    assert(word == "{");

    Eigen::Vector3f min, max;

    shared_ptr<Box> box;
    std::string currentBlock;

    //parse min vector
    while (currentBlock.length() < 2 || currentBlock.at(currentBlock.length() - 2) != '>')
    {
        input >> word;
        currentBlock += word;
    }
    currentBlock.pop_back();
    min = parseVector(currentBlock);

    currentBlock.clear();

    //parse max vector
    while (currentBlock.length() < 2 || (currentBlock.at(currentBlock.length() - 2) != '>' &&
        currentBlock.at(currentBlock.length() - 1) != '>'))
    {
        input >> word;
        currentBlock += word;
    }
    if (currentBlock.back() != '>')
        currentBlock.pop_back();
    max = parseVector(currentBlock);
    currentBlock.clear();
    box.reset(new Box(min, max));
    while (getline(input, word))
        currentBlock += word;
    parseObjectModifiers(*box, currentBlock);
    return box;
}

shared_ptr<Shape> POVParser::parseSphere(std::string block)
{
    std::istringstream input(block);
    //cout << block << endl;
    std::string word;
    input >> word;
    assert(word == "{");

    Eigen::Vector3f center;
    float radius;
    //parse center
    string currentBlock;
    while(currentBlock.length() < 2 || currentBlock.at(currentBlock.length() - 2) != '>')
    {
        input >> word;
        currentBlock += word;
    }
    currentBlock.pop_back();
    center = parseVector(currentBlock);

    currentBlock.clear();
    //get radius
    input >> word;
    radius = stof(word);

    shared_ptr<Sphere> sphere = std::make_shared<Sphere>(radius,center);
    //get the rest for the modifiers
    while(getline(input,word))
        currentBlock += word;
    parseObjectModifiers(*sphere,currentBlock);
    return sphere;
}
/**
 http://www.povray.org/documentation/view/3.6.1/297/
 * example input:
    {
    <0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
    }
 */
shared_ptr<Shape> POVParser::parsePlane(std::string block)
{
    std::istringstream input(block);
    //cout << block << endl;
    std::string word;
    input >> word;
    assert(word == "{");

    Eigen::Vector3f center,normal;
    //parse normal
    string currentBlock;
    while(currentBlock.length() < 2 || currentBlock.at(currentBlock.length() - 2) != '>')
    {
        input >> word;
        currentBlock += word;
    }
    //remove comma
    currentBlock.pop_back();
    normal = parseVector(currentBlock);
    //todo normalized?
    normal.normalize();
    currentBlock.clear();
    //get distance
    input >> word;
    center = normal * stof(word);
    shared_ptr<Plane> plane;
    plane.reset(new Plane(center, normal));
    //get the rest for the modifiers
    while(getline(input,word))
    {
        currentBlock += word;
        currentBlock += '\n';
    }

    parseObjectModifiers(*plane,currentBlock);
    return plane;
}

shared_ptr<Shape> POVParser::parseTriangle(std::string block)
{
    std::istringstream input(block);
    std::string word, currentBlock;
    input >> word;
    assert(word == "{");
    Eigen::Vector3f a,b,c;
    //get a
    while (currentBlock.length() < 2 || currentBlock.at(currentBlock.length() - 2) != '>')
    {
        input >> word;
        currentBlock += word;
    }
    //remove comma
    currentBlock.pop_back();
    a = parseVector(currentBlock);
    // get b
    currentBlock.clear();
    while (currentBlock.length() < 2 || currentBlock.at(currentBlock.length() - 2) != '>')
    {
        input >> word;
        currentBlock += word;
    }
    //remove comma
    currentBlock.pop_back();
    b = parseVector(currentBlock);
    //get c
    currentBlock.clear();
    while (currentBlock.length() < 2 || (currentBlock.at(currentBlock.length() - 2) != '>' &&
        currentBlock.at(currentBlock.length() - 1) != '>'))
    {
        input >> word;
        currentBlock += word;
    }
    //remove comma
    if (currentBlock.back() != '>')
        currentBlock.pop_back();
    c = parseVector(currentBlock);
    //get the rest for the modifiers
    currentBlock.clear();
    while (getline(input, word))
    {
        currentBlock += word;
        currentBlock += '\n';
    }
    shared_ptr<Triangle> triangle;
    triangle.reset(new Triangle(a, b, c));
    parseObjectModifiers(*triangle, currentBlock);
    return triangle;
}



std::string POVParser::parseComments(std::string &fileString) {

    bool inLineComment = false, inBlockComment = false;
    std::string finalString;
    for (unsigned int i = 0; i < fileString.length(); i++)
    {
        if(fileString[i] == '/' && (i + 1) < fileString.length())
        {
            if(fileString[i + 1] == '/' && !inBlockComment)
            {
                inLineComment = true;
            }
            if(fileString[i + 1] == '*' && !inLineComment)
            {
                inBlockComment = true;
            }
        }
        if(!inBlockComment && !inLineComment)
        {
            finalString += fileString[i];
            if (finalString.back() == '}' || finalString.back() == '>')
            {
                //finalString.insert(finalString.length() - 1," ");
                finalString += " ";
            }
        }
        if(fileString[i] == '\n' && inLineComment)
        {
            inLineComment = false;
        }
        if(fileString[i] == '*' && (i + 1) < fileString.length()
           && fileString[i + 1] == '/')
        {
            inBlockComment = false;
        }
    }
    return finalString;
}
/**
 * http://www.povray.org/documentation/view/3.6.2/321/
 * 11 total obect modifiers to parse, not including TRANSFORMATION, discussed at
 * http://www.povray.org/documentation/view/3.6.1/49/
 *
 * for now, this will parse out finish (ambient specular diffuse. maybe roughness?), and
 * solod color pigments
 *
 * sample input:
 * pigment
   {
    color rgb <1.0, 0.0, 1.0>
   }
  finish
  {
    ambient 0.2 diffuse 0.4
  }
 */
Shape &POVParser::parseObjectModifiers(Shape &shape, std::string block)
{
    istringstream input(block);
    string word;
    bool pigmentParse = false,finishParse = false;
    while(input >> word)
    {
        std::string testin = input.str().substr(input.tellg());
        if (word == "scale")
        {
            std::string vecstring;
            while (vecstring.back() != '>')
            {
                input >> word;
                vecstring += word;
            }
            Eigen::VectorXf vec = parseVector(vecstring, 3);
            vec.resize(3);
            shape.getTransform().addScale(vec);
        }
        if (word == "rotate")
        {
            std::string vecstring;
            while (vecstring.back() != '>')
            {
                input >> word;
                vecstring += word;
            }
            Eigen::VectorXf vec = parseVector(vecstring, 3);
            vec.resize(3);
            shape.getTransform().addRotate(vec);
        }
        if (word == "translate")
        {
            std::string vecstring;
            while (vecstring.back() != '>')
            {
                input >> word;
                vecstring += word;
            }
            Eigen::VectorXf vec = parseVector(vecstring, 3);
            vec.resize(3);
            shape.getTransform().addTranslate(vec);
        }
        if(word == "pigment")
        {
            pigmentParse = true;
            input >> word;
            assert(word.front() == '{');
            word.erase(0,1);
        }
        if(word == "finish")
        {
            finishParse = true;
            input >> word;
            assert(word.front() == '{');
            //pop off { and move on if there's stuff to inp
            word.erase(0,1);
        }

        if(!word.empty() && pigmentParse)
        {
            //add full color support soon
            assert(word == "color");
            //parse color type
            input >> word;
            //todo assert if this is the right color
            string colortype = word;
            string block;
            //parse color value
            while (block.size() < 2 || (block[block.size() - 2] != '>' &&
                block[block.size() - 3] != '>'))
            {
                input >> word;
                block += word + " ";
            }
            //take off } (second to last, because space) if it's there
            if (block[block.size() - 3] == '>')
            {
                block.erase(block.length() - 2, block.length() - 2);
            }
            VectorXf vec(colortype.size());
            vec = parseVector(block,colortype.size());
            //put color in
            std::transform(colortype.begin(), colortype.end(), colortype.begin(), ::tolower);
            for (unsigned int i = 0; i < colortype.size(); i++)
            {
                char letter = colortype[i];
                if(letter == 'r')
                    shape.getColor().r = vec[i];
                else if(letter == 'g')
                    shape.getColor().g = vec[i];
                else if(letter == 'b')
                    shape.getColor().b = vec[i];
                else if(letter == 'f')
                    shape.getColor().f = vec[i];
                else if(letter == 't')
                    shape.getColor().t = vec[i];
                else
                    cout << "warning: " << letter << " no a recognized param. ignoring...";
            }
            if (word.back() != '}')
                input >> word;
            assert(word.back() == '}');
            pigmentParse = false;
        }

        if(!word.empty() && finishParse)
        {
            while(word != "}")
            {
                std::string testin = input.str().substr(input.tellg());
                if(word == "ambient")
                {
                    VectorXf vec;
                    input >> word;
                    //proper rgb style. Ambient doesn't use ft
                    if(word == "rgb")
                    {
                        vec.resize(3);
                        string block;
                        while(block.empty() || block.back() != '>')
                        {
                            input >> word;
                            block += word;
                        }
                        vec = parseVector(block);
                        shape.getMaterial().ambient.setRGB(Vector3f(vec.segment(0, 3)));
                    }
                    else if (word == "rgbf")
                    {
                        vec.resize(4);
                        string block;
                        while (block.empty() || block.back() != '>')
                        {
                            input >> word;
                            block += word;
                        }
                        vec = parseVector(block);
                        shape.getMaterial().ambient.setRGBF(Vector4f(vec.segment(0, 4)));
                    }
                    //short hand num statement
                    else
                    {
                        vec.resize(3);
                        float num = stof(word);
                        vec << num,num,num;
                        shape.getMaterial().ambient.setRGB(Vector3f(vec.segment(0, 3)));
                    }

                }
                else if(word == "diffuse")
                {
                    input >> word;
                    shape.getMaterial().diffusePercent = stof(word);
                }
                else if(word == "specular")
                {
                    input >> word;
                    shape.getMaterial().specularPercent = stof(word);
                }
                else if(word == "roughness")
                {
                    input >> word;
                    shape.getMaterial().roughness = stof(word);
                }
                else if (word == "reflection")
                {
                    input >> word;
                    shape.getMaterial().reflection = stof(word);
                }
                else if (word == "refraction")
                {
                    input >> word;
                    shape.getMaterial().refraction = stof(word);
                }
                else if (word == "ior")
                {
                    input >> word;
                    shape.getMaterial().ior = stof(word);
                }
                if (word.back() == '}')
                    break;

                input >> word;
            }
            finishParse = false;
        }
    }
    shape.getMaterial().ambient.setRGB(shape.getMaterial().ambient.getRGB().array() *
        shape.getColor().getRGB().array());
    shape.getMaterial().ambient.f = shape.getColor().f; //yeah.... fix this soon
    return shape;
}



/*
 * // comments
• camera
• light_source
• translate, scale, rotate *
• box *
• sphere
• plane
• triangle *
• pigment
    o color
        § rgb
        § rgbf
• finish *
    o ambient
    o diffuse
    o specular
    o roughness
    o reflection
    o refraction
    o ior
 */

Scene *POVParser::parseFile(const std::string filepath)
{
    Scene *scene;
    if (SceneContext::octreeAcceleration)
        scene = new OctreeScene(0);
    else if (SceneContext::bvhAcceleration)
        scene = new BVHScene();
    else
        scene = new Scene();

    //open the file
    std::ifstream testFile;
    testFile.open(filepath);
    std::string content( (std::istreambuf_iterator<char>(testFile) ),
                         (std::istreambuf_iterator<char>()));
    //parse out the comments
    content = parseComments(content);

    std::istringstream fileToParse(content);
    std::string word;
    //go word by word
    while(fileToParse >> word)
    {
        std::string block;
        fileToParse >> block;
        assert(block.front() == '{');
        block += " ";
        if (block[1] != ' ')
            block.insert(1, " ");
        int innerBlocks = 0;
        //extract the next block of code for the right parser to parse
        do
        {
            if(innerBlocks > 0 && block.at(block.length() - 2) == '}')
                innerBlocks--;

            std::string word2;
            if(fileToParse >> word2)
            {
                if(word2.front() == '{')
                    innerBlocks++;
                block += word2 + ' ';
            }
            else
                break;

        }
        while(block.at(block.length() - 2) != '}' || innerBlocks > 0);

        assert(block.at(block.length() - 2) == '}');
        if (block.at(block.length() - 3) != ' ')
        {
            block.insert(block.length() - 2, " ");
        }
        //pass block to right parser
        if(word == "camera")
            scene->addCamera(parseCamera(block));
        else if(word == "light_source")
            scene->addLight(parseLight(block));
        else if(word == "sphere")
            scene->addShape(parseSphere(block));
        else if(word == "plane")
            scene->addShape(parsePlane(block));
        else if (word == "triangle")
            scene->addShape(parseTriangle(block));
        else if (word == "box")
            scene->addShape(parseBox(block));
    }
    //cout << "finished parsing" << filepath << endl;
    for (auto shape: scene->getObjects())
        shape->initTransformation();
    return scene;
}




