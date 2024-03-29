//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_SCENE_H
#define RAYTRACER473_SCENE_H


#include <string>
#include <geometry/Shape.h>
#include <lights/Light.h>
#include <memory>
#include <antialiasing/Sampler.h>
#include "cameras/Camera.h"

class Scene
{
protected:
    std::vector<std::shared_ptr<Shape>> objects;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<char> pixelBuffer;
    const int width, height;
    Eigen::Vector3i backgroundColor;
public:
    Scene();
    virtual void init();
    virtual void render(Camera& camera);

    std::shared_ptr<Camera> getCamera(int index);
    Shape& getShape(int index);
    Light& getLight(int index);

    std::vector<std::shared_ptr<Light>> getLights() const {return lights;}
    std::vector<std::shared_ptr<Shape>> getObjects() const {return objects;}

    void pushPixel(char r, char g, char b);
    void pushPixelf(float r, float g, float b);
    void pushPixelf(Eigen::Vector3f rgb);
    void renderImage(const std::string& writePath = "sample.tga");
    virtual HitData castRay(const Ray& ray, int depth = 0) const;
    virtual bool shadowHit(const Ray& ray, float currentMin) const;

    void pushPixel(Color matrix);

    void addLight(std::shared_ptr<Light> light);
    virtual void addShape(std::shared_ptr<Shape> shape);
    void addCamera(std::shared_ptr<Camera> camera);
};


#endif //RAYTRACER473_SCENE_H
