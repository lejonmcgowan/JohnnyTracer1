//
// Created by lejonmcgowan on 5/10/16.
//

#ifndef RAYTRACER473_MATERIALDATA_H
#define RAYTRACER473_MATERIALDATA_H
#include "Ray.h"
#include "Color.h"
struct BounceData
{
    int bounceIndex;
    float timeCollided;
    Ray ray;
    Eigen::Vector3f hitPoint;
    Color ambient, diffuse, specular;
    std::string type;
    BounceData()
    {
       bounceIndex = 0;
    }
};
#endif //RAYTRACER473_MATERIALDATA_H
