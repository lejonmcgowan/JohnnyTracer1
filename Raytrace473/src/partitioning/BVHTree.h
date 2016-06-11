//
// Created by lejonmcgowan on 6/3/16.
//

#ifndef RAYTRACER473_BVHTREE_H
#define RAYTRACER473_BVHTREE_H


#include <memory>
#include <geometry/Shape.h>
class BVHTree
{
public:
    void init(std::vector<std::shared_ptr<Shape>>& objects);
    bool getNearestShape(const Ray& ray, HitData& data) const;
    inline bool isLeaf() const { return left == nullptr && right == nullptr; }
//Private enum for iterating through xyz axis
    enum class SortAxis
    {
        X, Y, Z
    };
private:
    bool getNearestShape(const Ray& ray, HitData& data, float currentMin) const;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<BoundingBox> bbox;
    std::shared_ptr<BVHTree> left, right;
    static SortAxis GetLongestAxis(const std::vector<std::shared_ptr<Shape>>& objects);
    static void SortObjects(std::vector<std::shared_ptr<Shape>>& objects, BVHTree::SortAxis sortAxis);

    void fillShadeData(HitData& data, HitData& newData) const;
};


#endif //RAYTRACER473_BVHTREE_H
