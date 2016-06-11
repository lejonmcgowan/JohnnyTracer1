//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_HITDATA_H
#define RAYTRACER473_HITDATA_H


#include <Eigen/Dense>
#include "Color.h"
#include "Ray.h"
#include "BounceData.h"

class Material;
class Scene;
struct HitData
{
    bool hit;
    float timeCollided;
    Eigen::Vector3f hitPoint;
    Eigen::Vector3f normal;
    Color color;
    Material *material;
    Material *currentMaterial;
    Material *previousMaterial;
    Ray ray;
    Ray shadowRay;
    const Scene* scene;
    HitData(const Scene *scene, Material *initMaterial);
    HitData(const Scene *scene);
    int index;
    int depth;
    std::vector<BounceData> bounceInfo;
    Ray transformedRay;
    bool transformed;

};


#endif //RAYTRACER473_HITDATA_H
