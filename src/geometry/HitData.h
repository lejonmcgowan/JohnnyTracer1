//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_HITDATA_H
#define RAYTRACER473_HITDATA_H


#include <Eigen/Dense>
#include "Color.h"

struct HitData
{
    bool hit;
    float timeCollided;
    Eigen::Vector3f hitPoint;
    Eigen::Vector3f normal;
    Color color;
};


#endif //RAYTRACER473_HITDATA_H
