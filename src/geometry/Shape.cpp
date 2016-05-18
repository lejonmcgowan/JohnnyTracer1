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