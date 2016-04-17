//
// Created by lejonmcgowan on 4/12/16.
//
#include <geometry/Color.h>
#include <geometry/Transform.h>
#include "Light.h"

const Transform& Light::getTransform() const
{
    return transform;
}
void Light::setTransform(Transform& transform)
{
    Light::transform = transform;
}
const Color& Light::getColor() const
{
    return color;
}
void Light::setColor(Color& color)
{
    Light::color = color;
}
Light::Light(Transform transform, Color color): transform(transform), color(color)
{

}
Light::Light(Eigen::Vector3f location, Color color): transform(Transform()), color(color)
{
    transform.setTranslate(location);
}

Light::Light():transform(Transform()),color(Color())
{

}

