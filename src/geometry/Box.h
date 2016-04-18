//
// Created by lejonmcgowan on 4/14/16.
//

#ifndef RAYTRACER473_BOX_H
#define RAYTRACER473_BOX_H


#include "Shape.h"

class Box: public Shape
{

public:
    Box(float legnth, float width, float depth);
    virtual bool hit(const Ray& ray, float& t) override;
    virtual bool hit(const Ray& ray, HitData& hitData) override;
};


#endif //RAYTRACER473_BOX_H
