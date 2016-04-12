//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_SCENE_H
#define RAYTRACER473_SCENE_H


#include <string>
#include <geometry/Shape.h>
#include <memory>

class Scene
{
private:
    std::vector<std::shared_ptr<Shape>> objects;
    std::vector<char> pixelBuffer;
public:
    const int width, height;
    Eigen::Vector3i backgroundColor;
    Scene(int width, int height, Eigen::Vector3i backgroundColor);
    void init(const std::string& sceneDataPath);
    void addObject(std::shared_ptr<Shape> shape);

    void pushPixel(char r, char g, char b);
    void pushPixelf(float r, float g, float b);
    void pushPixelf(Eigen::Vector3f rgb);
    void renderImage(const std::string& writePath);
    HitData castRay(const Ray& ray) const;

    void pushPixel(Eigen::Vector3i matrix);
};


#endif //RAYTRACER473_SCENE_H
