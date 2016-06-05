//
// Created by lejonmcgowan on 4/14/16.
//

#ifndef RAYTRACER473_BOX_H
#define RAYTRACER473_BOX_H


#include "Shape.h"

class Box: public Shape
{
private:
    Eigen::Vector3f min, max;
    int tnearIndex, tfarIndex;
public:
    Box(Eigen::Vector3f min, Eigen::Vector3f max);
    virtual bool hit(const Ray& ray, float& t) override;
    virtual bool hit(const Ray& ray, HitData& hitData) override;
    virtual std::shared_ptr<BoundingBox> getBBox() override;

};


#endif //RAYTRACER473_BOX_H
