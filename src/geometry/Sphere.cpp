//
// Created by lejonmcgowan on 4/7/16.
//

#include <util/Constants.h>
#include "Sphere.h"

bool Sphere::hit(const Ray &ray, HitData &shadeData) const 
{
    float a = ray.origin.dot(ray.direction);
    float b = ray.direction.dot(2.0f * (ray.origin - center));
    float c = (ray.origin - center).dot(ray.origin - center) - radius * radius;
    float determinant = b * b - 4 * a * c;
    //check determinant to see if collision
    if(determinant < 0)
        return false;
    else
    {
        float t;
        //test small root for within epsilon
        t = -b - std::sqrt(determinant) / (2 * a);
        if (t > Constants::EPSILON)
        {
            shadeData.hit = true;
            shadeData.color = color;
            shadeData.timeCollided = t;
            shadeData.hitPoint = ray.origin + t * ray.direction;
            shadeData.normal = (shadeData.hitPoint - center) / radius;
            return true;
        }
        //small root wasn't within tracing range. Try long root
        t = -b + std::sqrt(determinant) / (2 * a);
        if (t > Constants::EPSILON)
        {
            shadeData.hit = true;
            shadeData.color = color;
            shadeData.timeCollided = t;
            shadeData.hitPoint = ray.origin + t * ray.direction;
            shadeData.normal = (shadeData.hitPoint - center) / radius;

            return true;
        }
        return false;
    }
}

