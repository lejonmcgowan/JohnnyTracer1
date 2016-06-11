//
// Created by lejonmcgowan on 6/3/16.
//

#ifndef RAYTRACER473_BVHSCENE_H
#define RAYTRACER473_BVHSCENE_H


#include <partitioning/BVHTree.h>
#include "Scene.h"
class BVHScene: public Scene
{
private:
    BVHTree tree;
    std::vector<std::shared_ptr<Shape>> unboundedShapes;
public:
    virtual bool shadowHit(const Ray& ray, float currentMin) const override;
    virtual void init() override;
    virtual void addShape(std::shared_ptr<Shape> shape) override;

    virtual HitData castRay(const Ray& ray, int depth) const override;

};


#endif //RAYTRACER473_BVHSCENE_H
