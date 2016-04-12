//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_POVPARSER_H
#define RAYTRACER473_POVPARSER_H


#include <string>
#include <cameras/Scene.h>

class POVParser
{
private:
    std::string parseComments(std::string& filepath);

    Eigen::Vector3f parseVector(std::string object);

    void parseCamera(std::string object);
    void parseLight(std::string object);
    void parseTransform(std::string object);
    void parseBox(std::string object);
    void parseSphere(std::string object);
    void parsePlane(std::string object);
    void parseTriangle(std::string object);
    void parsePigment(std::string object);
    void parseFinish(std::string object);

public:
    Scene parseFile(std::string& filepath);
};


#endif //RAYTRACER473_POVPARSER_H
