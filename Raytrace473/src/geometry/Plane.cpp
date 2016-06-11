//
// Created by lejonmcgowan on 4/12/16.
//

#include <util/Constants.h>
#include "Plane.h"
using namespace Eigen;

Plane::Plane():Plane(Vector3f(0,0,0),Vector3f(0,0,0))
{

}

Plane::Plane(Eigen::Vector3f center, Eigen::Vector3f normal):center(center),normal(normal)
{

}

bool Plane::hit(const Ray& ray, HitData& shadeData)
{
    float t = (center - ray.origin).dot(normal) / ray.direction.dot(normal);
    if(t > Constants::EPSILON)
    {
        shadeData.hit = true;
        shadeData.color = color;
        shadeData.timeCollided = t;
        shadeData.normal = normal;
        shadeData.hitPoint = ray.direction * t + ray.origin;
        shadeData.material = &material;
        return true;
    }

    return false;
}
bool Plane::hit(const Ray& ray, float& t)
{
    t = (center - ray.origin).dot(normal) / ray.direction.dot(normal);
    return t > Constants::EPSILON;
}

std::shared_ptr<BoundingBox> Plane::getBBox()
{
    return std::shared_ptr<BoundingBox>();
}
