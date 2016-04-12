//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_SHAPE_H
#define RAYTRACER473_SHAPE_H

#include "Ray.h"
#include "HitData.h"
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

class Shape
{
protected:
    Eigen::Vector3f color;
public:
    virtual bool hit(const Ray& ray, HitData& shadeData) const = 0;
    void setColor(Eigen::Vector3f color){this-> color = color;}
    Eigen::Vector3f& getColor(){return color;}
    virtual ~Shape(){}
};


#endif //RAYTRACER473_SHAPE_H
