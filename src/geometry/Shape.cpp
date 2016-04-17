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

const Transform& Shape::getTransform()
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