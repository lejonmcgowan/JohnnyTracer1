//
// Created by lejonmcgowan on 4/14/16.
//

#ifndef RAYTRACER473_TRIANGLE_H
#define RAYTRACER473_TRIANGLE_H


#include <Eigen/Dense>
#include "Shape.h"

class Triangle: public Shape
{
private:
    Eigen::Vector3f a, b, c;
public:
    Triangle(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c);

    virtual bool hit(const Ray& ray, HitData& hitData) override;
    virtual bool hit(const Ray& ray, float& t) override;

};


#endif //RAYTRACER473_TRIANGLE_H
