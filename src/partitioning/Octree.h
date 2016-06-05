//
// Created by lejonmcgowan on 5/18/16.
//

#ifndef RAYTRACER473_OCTREE_H
#define RAYTRACER473_OCTREE_H


#include <vector>
#include <geometry/Shape.h>
#include <memory>
//todo Clion why?
#include "../../ext/googletest/googletest/include/gtest/gtest_prod.h"
/*
 *Ray-octree intersection is credited to the Revelles et al.:
 * "An Efficient Parametric Algorithm for Octree Traversal (2000)"
 * http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.29.987
 */
class Octree: public std::enable_shared_from_this<Octree>
{
private:
    static int MAX_LEVEL;
    static int MAX_SHAPES;
    int level;
    int octant = -1;
    std::vector<std::shared_ptr<Shape>> objects;
    std::shared_ptr<Octree> nodes[8];
    unsigned int node_indices; //for node traversal
public:
    Eigen::Vector3f minBounds;
    Eigen::Vector3f maxBounds;

    Octree(int level);
    Octree(int level, Eigen::Vector3f minBounds, Eigen::Vector3f maxBounds);
    std::vector<std::vector<std::shared_ptr<Shape>>> getShapes(Ray ray);
    void clear();
    int printTree(std::string spaces = "");
    virtual void addShape(std::shared_ptr<Shape> shape);
private:
    int getIndex(std::shared_ptr<Shape> shape);
    bool inTree(std::shared_ptr<Shape> shape);
    void split();
    void proc_subtree(double tx0, double ty0, double tz0, double tx1, double ty1, double tz1,
                      Octree *tree, Ray ray, std::vector<std::vector<std::shared_ptr<Shape>>>& shapeTraversal);
    void ray_octree_traversal(Ray ray, std::vector<std::vector<std::shared_ptr<Shape>>>& shapeTraversal);
private:
    //TESTING todo: make these singluar tests into a fixture
    FRIEND_TEST(OctreeTest, splitTest);
    FRIEND_TEST(OctreeTest, selfSplitTest);
    FRIEND_TEST(OctreeTest, inTreeTest);
    FRIEND_TEST(OctreeTest, indexTest);
    FRIEND_TEST(OctreeTest, simpleRay);
};


#endif //RAYTRACER473_OCTREE_H
