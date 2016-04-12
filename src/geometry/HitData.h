//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_HITDATA_H
#define RAYTRACER473_HITDATA_H


#include <Eigen/Dense>

struct HitData
{
    bool hit;
    float timeCollided;
    Eigen::Vector3f hitPoint;
    Eigen::Vector3f normal;
    Eigen::Vector3f color;
};


#endif //RAYTRACER473_HITDATA_H
