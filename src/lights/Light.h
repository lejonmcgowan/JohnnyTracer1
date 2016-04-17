//
// Created by lejonmcgowan on 4/12/16.
//
#ifndef RAYTRACER473_LIGHT_H
#define RAYTRACER473_LIGHT_H

#include <geometry/Transform.h>
#include <geometry/Color.h>
#include <Eigen/Dense>

/**
 * http://www.povray.org/documentation/view/3.6.0/308/
 */
class Light
{
protected:
    Transform transform; //for position, and perhaps rotation. Only position is relevant for all
    // lights
    Color color; //for RGB, FT are ignored
public:
    Light(Transform transform, Color color);
    Light(Eigen::Vector3f location, Color color);
    Light();

    const Transform& getTransform() const ;
    const Color& getColor() const ;

    void setTransform(Transform& transform);
    void setColor(Color& color);
};


#endif //RAYTRACER473_LIGHT_H
