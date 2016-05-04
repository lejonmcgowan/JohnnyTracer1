//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_HITDATA_H
#define RAYTRACER473_HITDATA_H


#include <Eigen/Dense>
#include "Color.h"
#include "Ray.h"

class Material;
class Scene;
struct HitData
{
    bool hit;
    float timeCollided;
    Eigen::Vector3f hitPoint;
    Eigen::Vector3f normal;
    Color color;
    Material *material = nullptr;
    Ray ray;
    Ray shadowRay;
    const Scene* scene;

    HitData(const Scene* scene):scene(scene){}
    int index = -1;
    int depth = -1;
};


#endif //RAYTRACER473_HITDATA_H
