//
// Created by lejonmcgowan on 5/21/16.
//

#ifndef RAYTRACER473_BOUNDINGBOX_H
#define RAYTRACER473_BOUNDINGBOX_H


#include <Eigen/Dense>
#include "Ray.h"
class BoundingBox
{
private:
    Eigen::Vector3f min, max;
public:
    BoundingBox(Eigen::Vector3f min, Eigen::Vector3f max);
    Eigen::Vector3f getMin() { return min; }
    Eigen::Vector3f getMax() { return max; }
    inline Eigen::Vector3f getCenter() { return (max + min) / 2.0f; }

    bool hit(const Ray& ray);
    bool hit(const Ray& ray, float& tmin);
};


#endif //RAYTRACER473_BOUNDINGBOX_H
