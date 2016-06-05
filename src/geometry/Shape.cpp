//
// Created by lejonmcgowan on 4/7/16.
//
#include "Shape.h"

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
        Eigen::Vector3f newMin, newMax, transMin, transMax;
        Eigen::Vector4f bounds4Min, bounds4Max;
        bounds4Min << bbox->getMin()[0], bbox->getMin()[1], bbox->getMin()[2], 1;
        bounds4Max << bbox->getMax()[0], bbox->getMax()[1], bbox->getMax()[2], 1;
        bounds4Min = getTransform().getTransformMatrix() * bounds4Min;
        bounds4Max = getTransform().getTransformMatrix() * bounds4Max;

        transMin << bounds4Min[0], bounds4Min[1], bounds4Min[2];
        transMax << bounds4Max[0], bounds4Max[1], bounds4Max[2];

        for (int i = 0; i < 3; i++)
        {
            if (transMin[i] < transMax[i])
            {
                newMin[i] = transMin[i];
                newMax[i] = transMax[i];
            }
            else
            {
                newMin[i] = transMax[i];
                newMax[i] = transMin[i];
            }
        }

        return bbox;
    }
}