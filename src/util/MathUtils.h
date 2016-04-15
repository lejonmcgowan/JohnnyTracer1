//
// Created by lejonmcgowan on 4/12/16.
//

#ifndef RAYTRACER473_MATHUTILS_H
#define RAYTRACER473_MATHUTILS_H

#include <Eigen/Dense>

namespace MathHelper
{

    float mapCoords(float num, Eigen::Vector2f src, Eigen::Vector2f dest)
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
    Eigen::Vector2f mapCoords(Eigen::Vector2f coords, Eigen::Vector4f src, Eigen::Vector4f dest)
    {
        Eigen::Vector2f result;
        result << mapCoords(coords[0],Eigen::Vector2f(src[0],src[1]),Eigen::Vector2f(dest[0],dest[1])),
                  mapCoords(coords[1],Eigen::Vector2f(src[2],src[3]),Eigen::Vector2f(dest[2],dest[3]));

        return result;
    }
}
#endif //RAYTRACER473_MATHUTILS_H
