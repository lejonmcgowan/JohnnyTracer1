//
// Created by lejonmcgowan on 5/22/16.
//

#include <iostream>
#include <util/Constants.h>
#include "OctreeScene.h"


OctreeScene::OctreeScene(int level)
{
    octree = std::make_shared<Octree>(level);
}

void OctreeScene::init()
{
    //initialize cameras
    Scene::init();

    //setup boundaries todo: do this in one pass in POVParser
    bool init = false;
    Eigen::Vector3f min, max;
    for (auto shape: objects)
    {
        if (shape->getBBox() != nullptr)
        {
            auto bbox = shape->getBBox();
            for (int i = 0; i < 3; i++)
            {
                if (!init || bbox->getMin()[i] < min[i])
                {
                    min[i] = bbox->getMin()[i];
                }
                if (!init || bbox->getMax()[i] > max[i])
                {
                    max[i] = bbox->getMax()[i];
                }
            }

            if (!init)
                init = true;
        }
    }
    auto nearestPowerOfTwo = [](float num) -> float
    {
        int current = num < 0 ? -1 : 1;
        while (std::abs(current) < std::abs(num))
            current *= 2;

        return current;
    };
    min << nearestPowerOfTwo(min[0]), nearestPowerOfTwo(min[1]), nearestPowerOfTwo(min[2]);
    max << nearestPowerOfTwo(max[0]), nearestPowerOfTwo(max[1]), nearestPowerOfTwo(max[2]);
    octree->minBounds = min;
    octree->maxBounds = max;
    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;
    //now add in objects. All objects will be in the scene and will split automattically as needed
    for (auto shape: objects)
    {
        if (shape->getBBox() != nullptr)
        {
            octree->addShape(shape);
        }
        else
        {
            unBoundedShapes.push_back(shape);
        }
    }
    octree->printTree();
}

HitData OctreeScene::castRay(const Ray& ray, int depth) const
{
    HitData finalData(this);
    HitData shadeData(this);
    finalData.hit = false;
    finalData.ray = ray;
    finalData.depth = depth;
    bool firstTime = true;
    int i = 0;
    for (auto unboundShape: unBoundedShapes)
    {
        Ray intersectRay;
        //transformation checks
        if (unboundShape->isTransform())
        {
            intersectRay = unboundShape->toObjectSpace(ray);
        }
        else
        {
            intersectRay = ray;
        }
        if (unboundShape->hit(intersectRay, shadeData)
            && (shadeData.timeCollided < finalData.timeCollided || firstTime))
        {
            finalData.color = shadeData.color;
            finalData.timeCollided = shadeData.timeCollided;
            finalData.hit = true;
            finalData.hitPoint = shadeData.hitPoint;
            finalData.material = shadeData.material;
            finalData.normal = shadeData.normal;

            if (finalData.normal.dot(intersectRay.direction) > 0)
                finalData.normal *= -1;

            finalData.index = i;
            firstTime = false;
            if (unboundShape->isTransform())
            {
                //transform hit point
                finalData.hitPoint = ray.origin + finalData.timeCollided * ray.direction;
                //transform normal
                Eigen::Vector4f vector;
                vector << finalData.normal[0], finalData.normal[1], finalData.normal[2], 0;
                vector = unboundShape->getInvMat().transpose() * vector;
                finalData.normal << vector[0], vector[1], vector[2];
                finalData.normal.normalize();
                finalData.transformedRay = intersectRay;
            }
        }
        i++;

    }
    for (auto shapeList: octree->getShapes(ray))
    {
        bool hit = false;
        for (auto shape: shapeList)
        {
            Ray intersectRay;
            //transformation checks
            if (shape->isTransform())
            {
                intersectRay = shape->toObjectSpace(ray);
            }
            else
            {
                intersectRay = ray;
            }
            if (shape->hit(intersectRay, shadeData)
                && (shadeData.timeCollided < finalData.timeCollided || firstTime))
            {
                hit = true;
                finalData.color = shadeData.color;
                finalData.timeCollided = shadeData.timeCollided;
                finalData.hit = true;
                finalData.hitPoint = shadeData.hitPoint;
                finalData.material = shadeData.material;
                finalData.normal = shadeData.normal;

                if (finalData.normal.dot(intersectRay.direction) > 0)
                    finalData.normal *= -1;

                finalData.index = i;
                firstTime = false;
                if (shape->isTransform())
                {
                    //transform hit point
                    finalData.hitPoint = ray.origin + finalData.timeCollided * ray.direction;
                    //transform normal
                    Eigen::Vector4f vector;
                    vector << finalData.normal[0], finalData.normal[1], finalData.normal[2], 0;
                    vector = shape->getInvMat().transpose() * vector;
                    finalData.normal << vector[0], vector[1], vector[2];
                    finalData.normal.normalize();
                    finalData.transformedRay = intersectRay;
                }
            }
            i++;
        }
        if (hit)
            break;
    }
    return finalData;
}