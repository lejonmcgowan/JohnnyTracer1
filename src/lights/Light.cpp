//
// Created by lejonmcgowan on 4/12/16.
//
#include <geometry/Color.h>
#include <geometry/Transform.h>
#include <geometry/HitData.h>
#include <cameras/scenes/Scene.h>
#include "Light.h"

Color& Light::getColor()
{
    return color;
}
void Light::setColor(Color& color)
{
    Light::color = color;
}

Light::Light(Eigen::Vector3f location, Color color)
    : location(location), color(color)
{
}

Light::Light()
    : location(Eigen::Vector3f(0, 0, 0)), color(Color())
{

}
Eigen::Vector3f Light::getDirection(const HitData& hitdata)
{
    return (location - hitdata.hitPoint).normalized();
}

bool Light::inShadow(Ray& ray, HitData& data)
{
    float t;
    float distance = (location - ray.origin).norm();
    return data.scene->shadowHit(ray, distance);
}

void Light::setLocation(const Eigen::Vector3f location)
{
    this->location = location;
}
Eigen::Vector3f& Light::getLocation()
{
    return location;
}