//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_MATERIAL_H
#define RAYTRACER473_MATERIAL_H

#include <Eigen/Dense>

class Material
{
public:
    Eigen::Vector3f ambient;
    float diffusePercent = 0.6; //[0-1]
    float specular;
    float roughness = 0.05;    //[0.0005-1], like plastic by default
};


#endif //RAYTRACER473_MATERIAL_H
