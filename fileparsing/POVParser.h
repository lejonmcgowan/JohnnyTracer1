//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_POVPARSER_H
#define RAYTRACER473_POVPARSER_H


#include <string>
#include <cameras/scenes/Scene.h>
#include <lights/Light.h>

class POVParser
{
private:
    static std::string parseComments(std::string& filepath);

    static Eigen::VectorXf parseVector(std::string object, int size = 3);

    static std::shared_ptr<Camera> parseCamera(std::string object);
    static std::shared_ptr<Light>  parseLight(std::string object);
    static void parseTransform(std::string object);
    static std::shared_ptr<Shape> parseBox(std::string object);
    static std::shared_ptr<Shape> parseSphere(std::string object);
    static std::shared_ptr<Shape> parsePlane(std::string object);
    static std::shared_ptr<Shape> parseTriangle(std::string object);

    static Shape& parseObjectModifiers(Shape& shape, std::string block);
public:
    static Scene *parseFile(const std::string filepath);

    static Eigen::Vector3f parseMultVec(std::string numParse);
};


#endif //RAYTRACER473_POVPARSER_H
