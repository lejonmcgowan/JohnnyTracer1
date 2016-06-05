//
// Created by lejonmcgowan on 5/18/16.
//

#ifndef RAYTRACER473_OCTREESCENE_H
#define RAYTRACER473_OCTREESCENE_H


#include <vector>
#include <geometry/Shape.h>
#include <memory>
#include <partitioning/Octree.h>
#include <util/MathUtils.h>
#include "Scene.h"

class OctreeScene: public Scene
{
private:
    std::shared_ptr<Octree> octree;
    std::vector<std::shared_ptr<Shape>> unBoundedShapes;
public:
    OctreeScene(int level);
    virtual void init();
    virtual HitData castRay(const Ray& ray, int depth = 0) const override;

};


#endif //RAYTRACER473_OCTREESCENE_H
