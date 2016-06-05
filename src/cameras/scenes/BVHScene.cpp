//
// Created by lejonmcgowan on 6/3/16.
//

#include "BVHScene.h"
void BVHScene::init()
{
    tree.init(objects);
}

HitData BVHScene::castRay(const Ray& ray, int depth) const
{
    HitData finalData(this);
    HitData shadeData(this);
    finalData.hit = false;
    finalData.ray = ray;
    finalData.depth = depth;
    bool firstTime = true;
    int i = 0;
    for (auto unboundShape: unboundedShapes)
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
    if (tree.getNearestShape(ray, shadeData)
        && (shadeData.timeCollided < finalData.timeCollided || firstTime))
    {
        finalData.color = shadeData.color;
        finalData.timeCollided = shadeData.timeCollided;
        finalData.hit = true;
        finalData.hitPoint = shadeData.hitPoint;
        finalData.material = shadeData.material;
        finalData.normal = shadeData.normal;
        finalData.index = shadeData.index;
        //transform hit point
        finalData.hitPoint = ray.origin + finalData.timeCollided * ray.direction;
        finalData.transformedRay = shadeData.transformedRay;
        finalData.ray = shadeData.ray;
        finalData.shadowRay = shadeData.shadowRay;
        finalData.depth = shadeData.depth;
        finalData.transformed = shadeData.transformed;
    }
    return finalData;
}

void BVHScene::addShape(std::shared_ptr<Shape> shape)
{
    if (shape->getBBox() != nullptr)
        Scene::addShape(shape);
    else
        unboundedShapes.push_back(shape);
}

bool BVHScene::shadowHit(const Ray& ray, float currentMin) const
{
    float t;
    HitData filler(this);
    for (auto shape: unboundedShapes)
    {
        Ray timeRay;
        //transformation checks
        if (shape->isTransform())
        {
            timeRay = shape->toObjectSpace(ray);
        }
        else
        {
            timeRay = ray;
        }
        if (shape->hit(timeRay, t) && t < currentMin)
        {
            return true;
        }
    }
    return tree.getNearestShape(ray, filler);
}
