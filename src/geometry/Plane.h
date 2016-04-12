//
// Created by lejonmcgowan on 4/12/16.
//

#ifndef RAYTRACER473_PLANE_H
#define RAYTRACER473_PLANE_H


#include "Shape.h"

class Plane: public Shape
{
public:
    Plane();
    Plane(Eigen::Vector3f center, Eigen::Vector3f normal);

    virtual bool hit(const Ray& ray, HitData& shadeData) const override;

    //todo implement rule of three for plane class
private:
    Eigen::Vector3f center, normal;
};


#endif //RAYTRACER473_PLANE_H
