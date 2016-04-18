//
// Created by lejonmcgowan on 4/12/16.
//
#ifndef RAYTRACER473_LIGHT_H
#define RAYTRACER473_LIGHT_H

#include <geometry/Transform.h>
#include <geometry/Color.h>
#include <Eigen/Dense>
#include <geometry/Ray.h>
/**
 * http://www.povray.org/documentation/view/3.6.0/308/
 * Point light implementation (Since that's the default type in POVRAY).
 * todo abstract this and make a proper point light implementation
 */
class HitData;
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

    Transform& getTransform();
    Color& getColor();

    void setTransform(Transform& transform);
    void setColor(Color& color);

    Eigen::Vector3f getDirection(const HitData& hitdata);

    bool inShadow(Ray& ray, HitData& data);
};


#endif //RAYTRACER473_LIGHT_H
