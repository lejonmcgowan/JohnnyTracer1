//
// Created by lejonmcgowan on 4/12/16.
//
#include <geometry/Color.h>
#include <geometry/Transform.h>
#include <geometry/HitData.h>
#include <cameras/Scene.h>
#include "Light.h"

Transform& Light::getTransform()
{
    return transform;
}
void Light::setTransform(Transform& transform)
{
    Light::transform = transform;
}
Color& Light::getColor()
{
    return color;
}
void Light::setColor(Color& color)
{
    Light::color = color;
}
Light::Light(Transform transform, Color color): transform(transform), color(color)
{

}
Light::Light(Eigen::Vector3f location, Color color): transform(Transform()), color(color)
{
    transform.setTranslate(location);
}

Light::Light():transform(Transform()),color(Color())
{

}
Eigen::Vector3f Light::getDirection(const HitData& hitdata)
{
    return (transform.getTranslate() - hitdata.hitPoint).normalized();
}

bool Light::inShadow(Ray& ray, HitData& data)
{
    float t;
    float distance = (transform.getTranslate() - ray.origin).norm();
    const Scene* scene = data.scene;
    for(auto shape: scene->getObjects())
    {
        if(shape->hit(ray,t) && t < distance)
        {
            return true;
        }
    }

    return false;
}





