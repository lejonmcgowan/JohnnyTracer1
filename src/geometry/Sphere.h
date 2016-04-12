//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_SPHERE_H
#define RAYTRACER473_SPHERE_H


#include "Shape.h"

class Sphere: public Shape
{

private:
    Eigen::Vector3f center;
    float radius;
public:
    Sphere():radius(1.0f){}
    Sphere(float radius):radius(radius){}
    Sphere(float radius, Eigen::Vector3f center):radius(radius),center(center){};

    virtual bool hit(const Ray& ray, HitData& shadeData) const override;

    float getRadius() const {return radius;}
    void setRadius(float radius) {Sphere::radius = radius;}
    const Eigen::Vector3f &getCenter() const {return center;}
    void setCenter(const Eigen::Vector3f &center) {Sphere::center = center;}
    ~Sphere(){}
};
#endif //RAYTRACER473_SPHERE_H
