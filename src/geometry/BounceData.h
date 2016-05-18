//
// Created by lejonmcgowan on 5/10/16.
//

#ifndef RAYTRACER473_MATERIALDATA_H
#define RAYTRACER473_MATERIALDATA_H
#include "Ray.h"
#include "Color.h"
struct BounceData
{
    int bounceIndex = 0;
    float timeCollided;
    Ray ray;
    Eigen::Vector3f hitPoint;
    Color ambient, diffuse, specular;
    std::string type;
};
#endif //RAYTRACER473_MATERIALDATA_H
