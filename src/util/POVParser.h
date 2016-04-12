//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_POVPARSER_H
#define RAYTRACER473_POVPARSER_H


#include <string>
#include <cameras/Scene.h>
#include <lights/Light.h>

class POVParser
{
private:
    static std::string parseComments(std::string& filepath);

    static Eigen::Vector3f parseVector(std::string object);

    static std::shared_ptr<Camera> parseCamera(std::string object);
    static std::shared_ptr<Light>  parseLight(std::string object);
    static void parseTransform(std::string object);
    static void parseBox(std::string object);
    static std::shared_ptr<Shape> parseSphere(std::string object);
    static std::shared_ptr<Shape> parsePlane(std::string object);
    static void parseTriangle(std::string object);
    static void parsePigment(std::string object);
    static void parseFinish(std::string object);

public:
    static Scene parseFile(const std::string filepath);
};


#endif //RAYTRACER473_POVPARSER_H
