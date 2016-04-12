//
// Created by lejonmcgowan on 4/10/16.
//

#include <fstream>
#include "POVParser.h"
using namespace Eigen;
using namespace std;

Eigen::Vector3f POVParser::parseVector(std::string block)
{
    return Vector3f();
}

shared_ptr<Camera> POVParser::parseCamera(std::string block)
{

}

std::shared_ptr<Light> POVParser::parseLight(std::string block)
{

}

void POVParser::parseTransform(std::string block)
{

}

void POVParser::parseBox(std::string block)
{

}

shared_ptr<Shape> POVParser::parseSphere(std::string block)
{

}

shared_ptr<Shape> POVParser::parsePlane(std::string block)
{

}

void POVParser::parseTriangle(std::string block)
{

}

void POVParser::parsePigment(std::string block)
{

}

void POVParser::parseFinish(std::string block)
{

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

Scene POVParser::parseFile(const std::string filepath)
{
    Scene* scene = new Scene();
    //opoen the file
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
        std::string& tag = word;
        std::string block;
        fileToParse >> block;
        assert(block == "{");
        //extract the next block of code for the right parser to parse
        while(block.back() != '}')
        {
            fileToParse >> block;
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
    }

    return *scene;
}

std::string POVParser::parseComments(std::string &fileString) {

    bool inLineComment = false, inBlockComment = false;
    std::string finalString;
    for(int i = 0; i < fileString.length(); i++)
    {
        char testChar = fileString[i];
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


