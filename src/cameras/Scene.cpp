//
// Created by lejonmcgowan on 4/10/16.
//

#include <lights/Light.h>
#include <util/SceneContext.h>
#include "Scene.h"


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Scene::Scene():
        width(SceneContext::windowDims[0]),
        height(SceneContext::windowDims[1]),
        backgroundColor(Eigen::Vector3i(0,0,0))
{

}

void Scene::init(const std::string& sceneDataPath) {

}

void Scene::addShape(std::shared_ptr<Shape> shape)
{
    objects.push_back(shape);
}

void Scene::pushPixel(char r, char g, char b)
{
    pixelBuffer.push_back(r);
    pixelBuffer.push_back(g);
    pixelBuffer.push_back(b);
}

void Scene::pushPixelf(float r, float g, float b)
{
    pixelBuffer.push_back((char) (r * 255));
    pixelBuffer.push_back((char) (g * 255));
    pixelBuffer.push_back((char) (b * 255));
}

void Scene::pushPixelf(Eigen::Vector3f rgb)
{
   pushPixelf(rgb[0],rgb[1],rgb[2]);
}

void Scene::renderImage(const std::string& writePath)
{
    int result = stbi_write_tga(writePath.c_str(),width,height,3,&pixelBuffer[0]);
    assert(result);
    pixelBuffer.clear();
}


HitData Scene::castRay(const Ray &ray)  const
{
    HitData shadeData;
    double tmin = -1;
    bool firstTime;

    for(auto shape: objects)
    {
        if(shape->hit(ray,shadeData) && (shadeData.timeCollided < tmin || firstTime))
        {
            tmin = shadeData.timeCollided;
            shadeData.color = shape->getColor();
            firstTime = false;
        }
    }
    return shadeData;
}

void Scene::pushPixel(Eigen::Vector3i rgb)
{
    pushPixelf(rgb[0],rgb[1],rgb[2]);
}

void Scene::addCamera(std::shared_ptr<Camera> camera)
{
    cameras.push_back(camera);
}

void Scene::render(Camera &camera)
{
    camera.renderScene(*this);
}

Camera &Scene::getCamera(int index)
{
    return *cameras[index];
}

void Scene::addLight(std::shared_ptr<Light> light)
{
    //coming up. add a light to the scene. Light Data Structure TBD
}













