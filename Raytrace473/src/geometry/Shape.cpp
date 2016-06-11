//
// Created by lejonmcgowan on 4/7/16.
//
#include "Shape.h"
#include <iostream>

Material& Shape::getMaterial()
{
    return material;
}

void Shape::setMaterial(const Material& material)
{
    Shape::material = material;
}

Transform& Shape::getTransform()
{
    return transform;
}
void Shape::setTransform(const Transform& transform)
{
    Shape::transform = transform;
}
void Shape::setColor(Color color) { this->color = color; }

Color& Shape::getColor()
{
    return color;
}

Shape::~Shape() { }

void Shape::initTransformation()
{
    inverseTransform = transform.getTransformMatrix().inverse();
}
Ray Shape::toObjectSpace(const Ray& ray)
{
    Ray inverseRay;
    Eigen::Vector4f vectorO, vectorD;
    vectorO << ray.origin[0], ray.origin[1], ray.origin[2], 1;
    vectorD << ray.direction[0], ray.direction[1], ray.direction[2], 0;

    vectorO = inverseTransform * vectorO;
    vectorD = inverseTransform * vectorD;

    inverseRay.origin << vectorO[0], vectorO[1], vectorO[2];
    inverseRay.direction << vectorD[0], vectorD[1], vectorD[2];

    return inverseRay;
}
/*general flow of this will be:
 * 1. subclass will calculate the bounding box
 * 2. sublass will call superclasses (this)'s objects method to account for transformations
 * 3. this will return (untransformed) the same bounding box or (if transformed) a new bounding box around the
 * assumedly non-AABB box
 * */
std::shared_ptr<BoundingBox> Shape::getBBox()
{
    assert(bbox != nullptr);
    //if no transformations, simply return the bbox
    if (!getTransform().isTransform())
        return bbox;
        //else, bound the bounding box
    else
    {
        Eigen::Vector3f newMin(0,0,0), newMax(0,0,0), transMin, transMax;
        Eigen::Vector3f points[8];

        Eigen::Vector3f min = bbox->getMin();
        Eigen::Vector3f max = bbox->getMax();
        for(int i = 0; i < 8; i++)
        {
            points[i][0] = i & 0x1 ? min[0] : max[0];
            points[i][1] = i & 0x2 ? min[1] : max[1];
            points[i][2] = i & 0x4 ? min[2] : max[2];

            points[i] = transform.transformPoint(points[i]);
            //init the current min/max
            if(i == 0)
            {
                newMin = points[i];
                newMax = points[i];
            }

            newMin = newMin.cwiseMin(points[i]);
            newMax = newMax.cwiseMax(points[i]);
        }

        bbox.reset(new BoundingBox(newMin,newMax));
        std::cout << "MIN: (" << newMin[0] << "," << newMin[1] << "," << newMin[2] << ")" << std::endl;
        std::cout << "MAX: (" << newMax[0] << "," << newMax[1] << "," << newMax[2] << ")" << std::endl;
        return bbox;
    }
}