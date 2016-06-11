//
// Created by lejonmcgowan on 5/18/16.
//

#include "Octree.h"
#include <iostream>
#include <limits>

int Octree::MAX_LEVEL = 5;

int Octree::MAX_SHAPES = 10;

using namespace std;
Octree::Octree(int level, Eigen::Vector3f minBounds, Eigen::Vector3f maxBounds)
    : level(level),
      minBounds(minBounds),
      maxBounds(maxBounds)
{

}

Octree::Octree(int level)
    : Octree(level, Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 0, 0))
{

}

int first_node(double tx0, double ty0, double tz0, double txm, double tym, double tzm)
{
    unsigned char answer = 0;   // initialize to 00000000
    // select the entry plane and set bits
    if (tx0 > ty0)
    {
        if (tx0 > tz0)
        { // PLANE YZ
            if (tym < tx0) answer |= 2;    // set bit at position 1
            if (tzm < tx0) answer |= 1;    // set bit at position 0
            return (int) answer;
        }
    }
    else
    {
        if (ty0 > tz0)
        { // PLANE XZ
            if (txm < ty0) answer |= 4;    // set bit at position 2
            if (tzm < ty0) answer |= 1;    // set bit at position 0
            return (int) answer;
        }
    }
    // PLANE XY
    if (txm < tz0) answer |= 4;    // set bit at position 2
    if (tym < tz0) answer |= 2;    // set bit at position 1
    return (int) answer;
}

int new_node(double txm, int x, double tym, int y, double tzm, int z)
{
    if (txm < tym)
    {
        if (txm < tzm)
        { return x; }  // YZ plane
    }
    else
    {
        if (tym < tzm)
        { return y; } // XZ plane
    }
    return z; // XY plane;
}

void Octree::proc_subtree(double tx0, double ty0, double tz0, double tx1, double ty1, double tz1,
                          Octree *tree, Ray ray, vector<vector<shared_ptr<Shape>>>& shapeTraversal)
{
    float txm, tym, tzm;
    int currNode;
    shapeTraversal.push_back(objects);
    if (tx1 < 0 || ty1 < 0 || tz1 < 0) return;
    if (tree->nodes[0] == nullptr)
    {
        //cout << "Reached leaf node " << tree->level << " " << tree->octant <<  " Of size " << objects.size() << endl;
        return;
    }
    else
    {
        //cout << "Reached node " << tree->level << " " << tree->octant <<  " Of size " << objects.size() << endl;
    }

    txm = (float) (0.5 * (tx0 + tx1));
    tym = (float) (0.5 * (ty0 + ty1));
    tzm = (float) (0.5 * (tz0 + tz1));

    //check for NaNs
    if (isnan(txm))
    {
        if (ray.origin[0] < (minBounds[0] + maxBounds[0]) / 2)
        {
            txm = std::numeric_limits<float>::infinity();
        }
        else
        {
            txm = -std::numeric_limits<float>::infinity();
        }
    }
    if (isnan(tym))
    {
        if (ray.origin[1] < (minBounds[1] + maxBounds[1]) / 2)
        {
            tym = std::numeric_limits<float>::infinity();
        }
        else
        {
            tym = -std::numeric_limits<float>::infinity();
        }
    }
    if (isnan(tzm))
    {
        if (ray.origin[2] < (minBounds[2] + maxBounds[2]) / 2)
        {
            tzm = std::numeric_limits<float>::infinity();
        }
        else
        {
            tzm = -std::numeric_limits<float>::infinity();
        }
    }

    currNode = first_node(tx0, ty0, tz0, txm, tym, tzm);
    do
    {
        switch (currNode)
        {
            case 0:
            {
                proc_subtree(tx0, ty0, tz0, txm, tym, tzm, tree->nodes[node_indices].get(), ray, shapeTraversal);
                currNode = new_node(txm, 4, tym, 2, tzm, 1);
                break;
            }
            case 1:
            {
                proc_subtree(tx0, ty0, tzm, txm, tym, tz1, tree->nodes[1 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(txm, 5, tym, 3, tz1, 8);
                break;
            }
            case 2:
            {
                proc_subtree(tx0, tym, tz0, txm, ty1, tzm, tree->nodes[2 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(txm, 6, ty1, 8, tzm, 3);
                break;
            }
            case 3:
            {
                proc_subtree(tx0, tym, tzm, txm, ty1, tz1, tree->nodes[3 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(txm, 7, ty1, 8, tz1, 8);
                break;
            }
            case 4:
            {
                proc_subtree(txm, ty0, tz0, tx1, tym, tzm, tree->nodes[4 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(tx1, 8, tym, 6, tzm, 5);
                break;
            }
            case 5:
            {
                proc_subtree(txm, ty0, tzm, tx1, tym, tz1, tree->nodes[5 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(tx1, 8, tym, 7, tz1, 8);
                break;
            }
            case 6:
            {
                proc_subtree(txm, tym, tz0, tx1, ty1, tzm, tree->nodes[6 ^ node_indices].get(), ray, shapeTraversal);
                currNode = new_node(tx1, 8, ty1, 8, tzm, 7);
                break;
            }
            case 7:
            {
                proc_subtree(txm, tym, tzm, tx1, ty1, tz1, tree->nodes[7 ^ node_indices].get(), ray, shapeTraversal);
                currNode = 8;
                break;
            }
        }
    }
    while (currNode < 8);
}

void Octree::ray_octree_traversal(Ray ray, vector<vector<shared_ptr<Shape>>>& shapeTraversal)
{
    shapeTraversal.push_back(objects);
    node_indices = 0;
    Eigen::Vector3f size = minBounds;
    // fixes for rays with negative direction
    if (ray.direction[0] < 0)
    {
        ray.origin[0] = size[0] - ray.origin[0];
        ray.direction[0] = -ray.direction[0];
        node_indices |= 4; //bitwise OR (latest bits are XYZ)
    }
    if (ray.direction[1] < 0)
    {
        ray.origin[1] = size[1] - ray.origin[1];
        ray.direction[1] = -ray.direction[1];
        node_indices |= 2;
    }
    if (ray.direction[2] < 0)
    {
        ray.origin[2] = size[2] - ray.origin[2];
        ray.direction[2] = -ray.direction[2];
        node_indices |= 1;
    }
    double divx = 1 / ray.direction[0]; // IEEE stability fix
    double divy = 1 / ray.direction[1];
    double divz = 1 / ray.direction[2];

    double tx0 = (minBounds[0] - ray.origin[0]) * divx;
    double tx1 = (maxBounds[0] - ray.origin[0]) * divx;
    double ty0 = (minBounds[1] - ray.origin[1]) * divy;
    double ty1 = (maxBounds[1] - ray.origin[1]) * divy;
    double tz0 = (minBounds[2] - ray.origin[2]) * divz;
    double tz1 = (maxBounds[2] - ray.origin[2]) * divz;

    double maxt = max(max(tx0, ty0), tz0);
    double mint = min(min(tx1, ty1), tz1);
    if (maxt < mint)
    {
        proc_subtree(tx0, ty0, tz0, tx1, ty1, tz1, this, ray, shapeTraversal);
    }
}

std::vector<std::vector<std::shared_ptr<Shape>>> Octree::getShapes(Ray ray)
{
    std::vector<std::vector<std::shared_ptr<Shape>>> shapeTraversal;
    ray_octree_traversal(ray, shapeTraversal);
    return shapeTraversal;
}

void Octree::clear()
{
    objects.clear();
    for (auto child: nodes)
        child->clear();
}

int Octree::getIndex(std::shared_ptr<Shape> shape)
{
    int index = -1;

    auto shapeBounds = shape->getBBox();
    if (shapeBounds != nullptr)
    {
        Eigen::Vector3f midBounds = (maxBounds + minBounds) / 2.0f;

        Eigen::Vector3f shapeMinBounds = shapeBounds->getMin();
        Eigen::Vector3f shapeMidBounds = (shapeBounds->getMax() + shapeBounds->getMin()) / 2.0f;
        Eigen::Vector3f shapeMaxBounds = shapeBounds->getMax();

        bool topOctants = shapeMinBounds[1] > midBounds[1] && shapeMaxBounds[1] < maxBounds[1];
        bool bottomOctants = shapeMinBounds[1] > minBounds[1] && shapeMaxBounds[1] < midBounds[1];
        bool rightOctants = shapeMinBounds[0] > midBounds[0] && shapeMaxBounds[0] < maxBounds[0];
        bool leftOctants = shapeMinBounds[0] > minBounds[0] && shapeMaxBounds[0] < midBounds[0];
        bool backOctants = shapeMinBounds[2] > midBounds[2] && shapeMaxBounds[2] < maxBounds[2];
        bool frontOctants = shapeMinBounds[2] > minBounds[2] && shapeMaxBounds[2] < midBounds[2];

        if (topOctants)
        {
            if (leftOctants)
            {
                if (frontOctants)
                {
                    index = 2;
                }
                else if (backOctants)
                {
                    index = 3;
                }
            }
            else if (rightOctants)
            {
                if (frontOctants)
                {
                    index = 6;
                }
                else if (backOctants)
                {
                    index = 7;
                }
            }
        }
        else if (bottomOctants)
        {
            if (leftOctants)
            {
                if (frontOctants)
                {
                    index = 0;
                }
                else if (backOctants)
                {
                    index = 1;
                }
            }
            else if (rightOctants)
            {
                if (frontOctants)
                {
                    index = 4;
                }
                else if (backOctants)
                {
                    index = 5;
                }
            }
        }
    }
    return index;

}

bool Octree::inTree(std::shared_ptr<Shape> shape)
{
    bool result = true;
    auto bbox = shape->getBBox();
    if (bbox != nullptr)
    {

        Eigen::Vector3f shapeMin = bbox->getMin();
        Eigen::Vector3f shapeMax = bbox->getMax();

        for (int i = 0; i < 3; i++)
        {
            result &= shapeMin[i] < maxBounds[i] && shapeMax[i] > minBounds[i];
        }

        return result;
    }
    else
        return false;
}

//init for node children
void Octree::split()
{
    Eigen::Vector3f midBounds = (maxBounds - minBounds) / 2.0f;
    nodes[0] = std::make_shared<Octree>(level + 1, minBounds, midBounds);
    nodes[1] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0], minBounds[1], minBounds[2] + midBounds[2]),
                                        Eigen::Vector3f(midBounds[0], midBounds[1], maxBounds[2]));
    nodes[2] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0], minBounds[1] + midBounds[1], minBounds[2]),
                                        Eigen::Vector3f(midBounds[0], maxBounds[1], midBounds[2]));
    nodes[3] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0],
                                                        minBounds[1] + midBounds[1],
                                                        minBounds[2] + midBounds[2]),
                                        Eigen::Vector3f(midBounds[0], maxBounds[1], maxBounds[2]));
    nodes[4] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0] + midBounds[0], minBounds[1], minBounds[2]),
                                        Eigen::Vector3f(maxBounds[0], midBounds[1], midBounds[2]));
    nodes[5] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0] + midBounds[0],
                                                        minBounds[1],
                                                        minBounds[2] + midBounds[2]),
                                        Eigen::Vector3f(maxBounds[0], midBounds[1], maxBounds[2]));
    nodes[6] = std::make_shared<Octree>(level + 1,
                                        Eigen::Vector3f(minBounds[0] + midBounds[0],
                                                        minBounds[1] + midBounds[1],
                                                        minBounds[2]),
                                        Eigen::Vector3f(maxBounds[0], maxBounds[1], midBounds[2]));
    nodes[7] = std::make_shared<Octree>(level + 1, midBounds, maxBounds);

    for (int i = 0; i < 8; i++)
        nodes[i]->octant = i;
}

//add a shape to the lowest possible level of the octree hierarchy
void Octree::addShape(std::shared_ptr<Shape> shape)
{
    //make sure the shape is in the octree to begin with
    if (level != 0 || inTree(shape))
    {
        //check if there is a child to insert into
        if (nodes[0] != nullptr)
        {
            int index = getIndex(shape);
            if (index > -1)
            {
                nodes[index]->addShape(shape);
                return;
            }
            else
            {
                Eigen::Vector3f min = shape->getBBox()->getMin();
                Eigen::Vector3f max = shape->getBBox()->getMax();
                cout << min << "->" << max << " not in tree " << level << octant << endl;
            }
        }
        //child wasn't qualified, stored here
        objects.push_back(shape);
        //check for whether or not it is time to splie
        if (objects.size() > MAX_SHAPES && level < MAX_LEVEL)
        {
            //split if necessary
            if (nodes[0] == nullptr)
                split();
            //run through all objects on this level and distrubute as necessary
            for (unsigned int i = 0; i < objects.size();)
            {
                int index = getIndex(objects[i]);
                //found a child node that qualifies, insert
                if (index != -1)
                {
                    auto shape = objects[i];
                    objects.erase(objects.begin() + i);
                    nodes[index]->addShape(shape);
                }
                else
                {
                    i++;
                }
            }
        }
    }
}

int Octree::printTree(std::string spaces)
{
    int numChildren = objects.size();
    cout << spaces << "(" << level << "," << octant << "): " << numChildren << " objects" << endl;
    if (nodes[0] != nullptr)
    {
        for (auto child: nodes)
        {
            numChildren += child->printTree(spaces + "   ");
        }
    }
    if (spaces.empty())
        cout << "Total children: " << numChildren;
    return numChildren;
}






