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

bool Plane::hit(const Ray& ray, HitData& shadeData) const
{
    float t = (center - ray.origin).dot(normal) / ray.direction.dot(normal);
    if(t > Constants::EPSILON)
    {
        shadeData.timeCollided = t;
        shadeData.normal = normal;
        shadeData.hitPoint = ray.origin * t + ray.direction;

        return true;
    }

    return false;
}