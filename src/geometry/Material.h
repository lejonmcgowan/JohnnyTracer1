//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_MATERIAL_H
#define RAYTRACER473_MATERIAL_H

#include <Eigen/Dense>
#include "Color.h"
#include "HitData.h"

class HitData;
class Material
{
public:
    Color ambient, diffuse, specular;
    float diffusePercent = 0.6; //[0-1]
    float specularPercent = 0;
    float specularexp = 32;
    float roughness = 0.05f;    //[0.0005-1], like plastic by default
    float reflection = 0.0f;
    float refraction = 0.0f;
    float ior = 1.0f;
    Color shade(HitData& data);
    Eigen::Vector3f getReflectedColor(HitData& data);
    Eigen::Vector3f getRefractedColor(HitData& data);
};


#endif //RAYTRACER473_MATERIAL_H
