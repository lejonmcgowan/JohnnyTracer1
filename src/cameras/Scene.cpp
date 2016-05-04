//
// Created by lejonmcgowan on 4/10/16.
//

#include <lights/Light.h>
#include <util/SceneContext.h>
#include <util/MathUtils.h>
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
    r = MathHelper::clamp(r, 0.0f, 1.0f);
    g = MathHelper::clamp(g, 0.0f, 1.0f);
    b = MathHelper::clamp(b, 0.0f, 1.0f);

    pixelBuffer.push_back((unsigned char) (r * 255));
    pixelBuffer.push_back((unsigned char) (g * 255));
    pixelBuffer.push_back((unsigned char) (b * 255));
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

HitData Scene::castRay(const Ray& ray, int depth) const
{
    HitData finalData(this);
    HitData shadeData(this);
    finalData.hit = false;
    finalData.ray = ray;
    finalData.depth = depth;
    bool firstTime = true;
    int i = 0;
    for(auto shape: objects)
    {
        if (shape->hit(ray, shadeData)
            && (shadeData.timeCollided < finalData.timeCollided || firstTime))
        {
            finalData.color = shadeData.color;
            finalData.timeCollided = shadeData.timeCollided;
            finalData.hit = true;
            finalData.hitPoint = shadeData.hitPoint;
            finalData.material = shadeData.material;
            finalData.normal = shadeData.normal;
            finalData.index = i;
            firstTime = false;
        }
        i++;
    }
    return finalData;
}


void Scene::pushPixel(Color rgb)
{
    pushPixelf(rgb.r,rgb.g,rgb.b);
}

void Scene::addCamera(std::shared_ptr<Camera> camera)
{
    cameras.push_back(camera);
}

void Scene::render(Camera &camera)
{
    camera.renderScene(*this);
}

std::shared_ptr<Camera> Scene::getCamera(int index)
{
    return cameras[index];
}

void Scene::addLight(std::shared_ptr<Light> light)
{
    lights.push_back(light);
}
Shape& Scene::getShape(int index)
{
    return *objects[index];
}
Light& Scene::getLight(int index)
{
    return *lights[index];
}




















