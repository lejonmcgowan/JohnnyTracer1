//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_RAY_H
#define RAYTRACER473_RAY_H


#include <Eigen/Dense>

struct Ray
{
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
    Ray():origin(Eigen::Vector3f(0,0,0)),
          direction(Eigen::Vector3f(0,0,-1))
    {

    }

    Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction):
            origin(origin),
            direction(direction)
    {
    }
    Ray(const Ray& ray)
    {
        origin = ray.origin;
        direction = ray.direction;
    }

    Ray& operator=(const Ray& ray)
    {
        if (this == &ray)
            return (*this);

        origin = ray.origin;
        direction = ray.direction;

        return (*this);
    }
    ~Ray() = default;
};


#endif //RAYTRACER473_RAY_H
