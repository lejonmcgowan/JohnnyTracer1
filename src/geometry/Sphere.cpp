//
// Created by lejonmcgowan on 4/7/16.
//

#include <util/Constants.h>
#include "Sphere.h"

bool Sphere::hit(const Ray& ray, HitData& shadeData)
{
    float a = ray.direction.dot(ray.direction);
    const Eigen::Vector3f dist = ray.origin - center;
    float b = ray.direction.dot(2.0f * dist);
    float c = dist.dot(dist) - radius * radius;
    float determinant = b * b - 4 * a * c;

    //check determinant to see if collision
    if(determinant < 0)
        return false;
    else
    {
        float t;
        //test small root for within epsilon
        t = (-b - std::sqrt(determinant)) / (2 * a);
        if (t > Constants::EPSILON)
        {
            shadeData.hit = true;
            shadeData.color = color;
            shadeData.timeCollided = t;
            shadeData.hitPoint = ray.direction * t + ray.origin;
            shadeData.normal = (ray.direction * t + ray.origin - center) / radius;
            shadeData.material = &material;

            return true;
        }
        //small root wasn't within tracing range. Try long root
        //TODO: DRY. can probably abstract these if's into a better utility to assign stugg with
        t = (-b - std::sqrt(determinant)) / (2 * a);
        if (t > Constants::EPSILON)
        {
            shadeData.hit = true;
            shadeData.color = color;
            shadeData.timeCollided = t;
            shadeData.hitPoint = ray.direction * t + ray.origin;
            shadeData.normal = (shadeData.hitPoint - center) / radius;
            shadeData.material = &material;

            return true;
        }
        return false;
    }
}

bool Sphere::hit(const Ray& ray, float& t)
{
    float a = ray.direction.dot(ray.direction);
    const Eigen::Vector3f dist = ray.origin - center;
    float b = ray.direction.dot(2.0f * dist);
    float c = dist.dot(dist) - radius * radius;
    float determinant = b * b - 4 * a * c;

    //check determinant to see if collision
    if(determinant < 0)
        return false;

    t = (-b - std::sqrt(determinant)) / (2 * a);
    if(t > Constants::EPSILON)
        return true;

    t = (-b + std::sqrt(determinant)) / (2 * a);
    if(t > Constants::EPSILON)
        return true;

    return false;
}