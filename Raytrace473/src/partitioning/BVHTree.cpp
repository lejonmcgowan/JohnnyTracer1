//
// Created by lejonmcgowan on 6/3/16.
//

#include "BVHTree.h"
void BVHTree::init(std::vector<std::shared_ptr<Shape>>& objects)
{
    bbox.reset(new BoundingBox(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(0, 0, 0)));
    //you wot m8?
    if (objects.size() > 0)
    {
        //1: put it in
        if (objects.size() == 1)
        {
            shape = objects[0];
            bbox.reset(new BoundingBox(shape->getBBox()->getMin(),
                                       shape->getBBox()->getMax()));
        }
            //>1: pass the responsibility to your children
        else
        {
            //Sort and split recursivley, swapping the split axis each time.
            SortAxis axis = GetLongestAxis(objects);
            SortObjects(objects, axis);
            left = std::make_shared<BVHTree>();
            auto leftHalf = std::vector<std::shared_ptr<Shape>>(objects.begin(), objects.begin() + objects.size() / 2);
            left->init(leftHalf);
            right = std::make_shared<BVHTree>();
            auto rightHalf = std::vector<std::shared_ptr<Shape>>(objects.begin() + objects.size() / 2, objects.end());
            right->init(rightHalf);
            Eigen::Vector3f bMin = right->bbox->getMin().cwiseMin(left->bbox->getMin());
            Eigen::Vector3f bMax = right->bbox->getMax().cwiseMax(left->bbox->getMax());
            bbox.reset(new BoundingBox(bMin, bMax));
        }
    }
}

bool BVHTree::getNearestShape(const Ray& ray, HitData& data) const
{
    return getNearestShape(ray, data, -1);
}

BVHTree::SortAxis BVHTree::GetLongestAxis(const std::vector<std::shared_ptr<Shape>>& objects)
{
    Eigen::Vector3f minCoords, maxCoords;
    if (objects.size() > 0)
    {
        minCoords = objects[0]->getBBox()->getMin();
        maxCoords = objects[1]->getBBox()->getMax();
        for (int i = 1; i < objects.size(); i++)
        {
            //todo had no idea Eigen had this function. use in other places
            minCoords = minCoords.cwiseMin(objects[i]->getBBox()->getMin());
            maxCoords = maxCoords.cwiseMax(objects[i]->getBBox()->getMax());
        }
        Eigen::Vector3f diff = maxCoords - minCoords;
        SortAxis retAxis = diff(0) > diff(1) ? diff(0) > diff(2) ? SortAxis::X : SortAxis::Z :
                           diff(1) > diff(2) ? SortAxis::Y : SortAxis::Z;
        return retAxis;
    }
    return SortAxis::X;
}

bool compareBoxesX(const std::shared_ptr<Shape>& left, const std::shared_ptr<Shape>& right)
{
   return left->getBBox()->getCenter()[0] < right->getBBox()->getCenter()[0];
}

bool compareBoxesY(const std::shared_ptr<Shape>& left, const std::shared_ptr<Shape>& right)
{
   return left->getBBox()->getCenter()[1] < right->getBBox()->getCenter()[1];
}

bool compareBoxesZ(const std::shared_ptr<Shape>& left, const std::shared_ptr<Shape>& right)
{
   return left->getBBox()->getCenter()[2] < right->getBBox()->getCenter()[2];
}


void BVHTree::SortObjects(std::vector<std::shared_ptr<Shape>>& objects, BVHTree::SortAxis sortAxis)
{
    switch (sortAxis)
    {
        case SortAxis::X:
            std::sort(objects.begin(), objects.end(), compareBoxesX);
            break;
        case SortAxis::Y:
            std::sort(objects.begin(), objects.end(), compareBoxesY);
            break;
        case SortAxis::Z:
            std::sort(objects.begin(), objects.end(), compareBoxesZ);
            break;
    }
}

bool BVHTree::getNearestShape(const Ray& ray, HitData& data, float currentMin) const
{
    //First check to see if this hit intersects with this node.
    float thisMin = -0.5f;
    bool finalHit = false;
    HitData currentData(data.scene);
    data.ray = ray;
    currentData.ray = ray;
    if (bbox->hit(ray, thisMin) && (thisMin < currentMin || currentMin < 0))
    {
        //left condition
        if (this->left != nullptr)
        {
            auto childHit = left->getNearestShape(ray, currentData, currentMin);
            if (currentData.hit && (currentData.timeCollided < currentMin || currentMin < 0))
            {
                finalHit = childHit;
                currentMin = currentData.timeCollided;
                fillShadeData(data, currentData);
            }
        }
        //right condition
        if (this->right != nullptr)
        {
            auto childHit = right->getNearestShape(ray, currentData, currentMin);
            if (currentData.hit && (currentData.timeCollided < currentMin || currentMin < 0))
            {
                finalHit = childHit;
                fillShadeData(data, currentData);
            }
        }
        //leaf
        if (isLeaf())
        {
            Ray intersectRay;
            //transformation checks
            if (shape->isTransform())
            {
                intersectRay = shape->toObjectSpace(ray);
                data.transformedRay = intersectRay;
                data.transformed = true;
            }
            else
                intersectRay = ray;
            if (shape->getBBox()->hit(intersectRay))
            {
                finalHit = shape->hit(intersectRay, data);
                if(shape->isTransform())
                {
                    //transform hit point
                    //transform normal
                    Eigen::Vector4f vector;
                    vector << data.normal[0], data.normal[1], data.normal[2], 0;
                    vector = shape->getInvMat().transpose() * vector;
                    data.normal << vector[0], vector[1], vector[2];
                    data.normal.normalize();
                }
            }
        }
    }
    return finalHit;
}

void BVHTree::fillShadeData(HitData& finalData, HitData& shadeData) const
{
    Ray intersectRay;

    finalData.color = shadeData.color;
    finalData.ray = shadeData.ray;
    finalData.timeCollided = shadeData.timeCollided;
    finalData.hit = true;
    finalData.hitPoint = shadeData.hitPoint;
    finalData.material = shadeData.material;
    finalData.normal = shadeData.normal;
    finalData.hitPoint = shadeData.hitPoint;
    finalData.transformedRay = shadeData.transformedRay;
    //flip normal if necessary
    intersectRay = shadeData.transformed ? shadeData.transformedRay : shadeData.ray;
    if (finalData.normal.dot(intersectRay.direction) > 0)
        finalData.normal *= -1;

}





