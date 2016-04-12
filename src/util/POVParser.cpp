//
// Created by lejonmcgowan on 4/10/16.
//

#include <fstream>
#include "POVParser.h"
using namespace Eigen;
using namespace std;

std::string parseComments(std::string &fileString);
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

Scene POVParser::parseFile(std::string &filepath)
{
    Scene* scene = nullptr;
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
        //check for current state: parsing object block, parsing vector
        switch(word)
        {
            case "camera";
        }
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


Eigen::Vector3f POVParser::parseVector(std::string object) {
    return Eigen::Matrix<float, 3, 1, 0, 3, 1>();
}

void POVParser::parseCamera(std::string object) {

}

void POVParser::parseLight(std::string object) {

}

void POVParser::parseTransform(std::string object) {

}

void POVParser::parseBox(std::string object) {

}

void POVParser::parseSphere(std::string object) {

}

void POVParser::parsePlane(std::string object) {

}

void POVParser::parseTriangle(std::string object) {

}

void POVParser::parsePigment(std::string object) {

}

void POVParser::parseFinish(std::string object) {

}