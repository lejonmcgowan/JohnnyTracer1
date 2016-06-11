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
    int index;
    Color ambient, diffuse, specular;
    float diffusePercent; //[0-1]
    float specularPercent;
    float specularexp;
    float roughness;    //[0.0005-1], like plastic by default
    float reflection;
    float refraction;
    float ior;
    Color shade(HitData& data);
    Eigen::Vector3f getReflectedColor(HitData& data);
    Eigen::Vector3f getRefractedColor(HitData& data, bool& stillRefract);

    Material()
    {
         index = -1;
         diffusePercent = 0.6f;
         specularPercent = 0;
         specularexp = 32.0f;
         roughness = 0.05f;
         reflection = 0.0f;
         refraction = 0.0f;
         ior = 1.0f;
    }
};


#endif //RAYTRACER473_MATERIAL_H
