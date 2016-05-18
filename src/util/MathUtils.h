//
// Created by lejonmcgowan on 4/12/16.
//

#ifndef RAYTRACER473_MATHUTILS_H
#define RAYTRACER473_MATHUTILS_H

#include <Eigen/Dense>
#include "Constants.h"

namespace MathHelper
{

inline float mapCoords(float num, Eigen::Vector2f src, Eigen::Vector2f dest)
    {
        return (num - src[0]) / (src[1] - src[0]) * (dest[1] - dest[0]) + dest[0];
    }

    /**
     * maps one coordinate from one system to another. src and destination are of the form
     *
     * (xmin,xmax,ymin,ymax)
     *
     * coords is assumed to be a coordinate with in src's boundaries
     */
    inline Eigen::Vector2f mapCoords(Eigen::Vector2f coords, Eigen::Vector4f src, Eigen::Vector4f
    dest)
    {
        Eigen::Vector2f result;
        result << mapCoords(coords[0],Eigen::Vector2f(src[0],src[1]),Eigen::Vector2f(dest[0],dest[1])),
                  mapCoords(coords[1],Eigen::Vector2f(src[2],src[3]),Eigen::Vector2f(dest[2],dest[3]));

        return result;
    }

    inline bool equalsEpsilon(float a, float b, float epsilon = Constants::EPSILON)
    {
        return std::abs(a - b) < epsilon;
    }

    inline bool equalsEpsilon(Eigen::Vector2f a, Eigen::Vector2f b, float epsilon = Constants::EPSILON)
    {
        return equalsEpsilon(a[0],b[0],epsilon) && equalsEpsilon(a[1],b[1],epsilon);
    }

inline bool equalsEpsilon(Eigen::Vector3f a, Eigen::Vector3f b, float epsilon =
Constants::EPSILON)
    {
        return equalsEpsilon(a[0],b[0],epsilon) && equalsEpsilon(a[1],b[1],epsilon) && equalsEpsilon(a[2],b[2],epsilon);
    }

template<typename T>
T clamp(const T& n, const T& lower, const T& upper)
{
    return std::max(lower, std::min(n, upper));

}

inline float toRadians(float degrees)
{
    float rads = degrees * Constants::PI / 180.0f;
    return rads;
}
}
#endif //RAYTRACER473_MATHUTILS_H
