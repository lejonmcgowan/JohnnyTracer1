//
// Created by lejonmcgowan on 4/12/16.
//

#ifndef RAYTRACER473_SCENECONTEXT_H
#define RAYTRACER473_SCENECONTEXT_H


#include <Eigen/Dense>
#include <geometry/Color.h>

class SceneContext
{
public:
    static Eigen::Vector2i windowDims;
    static Color backgroundColor;
    static float aspect;
    static int numBounces;
    static int numSamples;
    static bool shadows;
    static bool octreeAcceleration, bvhAcceleration;
    static int octreeLevel;
    static int width(){return windowDims[0];}
    static int height(){return windowDims[1];}
};


#endif //RAYTRACER473_SCENECONTEXT_H
