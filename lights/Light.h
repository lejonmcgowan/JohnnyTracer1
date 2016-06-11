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
    Eigen::Vector3f location;
    // lights
    Color color; //for RGB, FT are ignored
public:
    Light(Eigen::Vector3f location, Color color);
    Light();

    Color& getColor();

    void setLocation(const Eigen::Vector3f location);
    Eigen::Vector3f& getLocation();

    void setColor(Color& color);

    Eigen::Vector3f getDirection(const HitData& hitdata);

    bool inShadow(Ray& ray, HitData& data);
};


#endif //RAYTRACER473_LIGHT_H
