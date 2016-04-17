//
// Created by lejonmcgowan on 4/16/16.
//

#include "Transform.h"

Transform::Transform()
    : translate(Eigen::Vector3f(0, 0, 0)),
      rotate(Eigen::Vector3f(0, 0, 0)),
      scale(Eigen::Vector3f(1, 1, 1))
{

}

Transform::Transform(Eigen::Vector3f translate, Eigen::Vector3f rotate, Eigen::Vector3f scale)
{

}

const Eigen::Vector3f& Transform::getTranslate() const
{
    return translate;
}

const Eigen::Vector3f& Transform::getRotate() const
{
    return rotate;
}

const Eigen::Vector3f& Transform::getScale() const
{
    return scale;
}

void Transform::setTranslate(const Eigen::Vector3f& translate)
{
    Transform::translate = translate;
}

void Transform::setRotate(const Eigen::Vector3f& rotate)
{
    Transform::rotate = rotate;
}

void Transform::setScale(const Eigen::Vector3f& scale)
{
    Transform::scale = scale;
}

void Transform::scaleBy(Eigen::Vector3f scale)
{
    this->scale += scale;
}

void Transform::scaleBy(float other)
{
    scale[0] *= other;
    scale[1] *= other;
    scale[2] *= other;
}

void Transform::scaleByMult(Eigen::Vector3f other)
{
    scale[0] *= other[0];
    scale[1] *= other[1];
    scale[2] *= other[2];
}

void Transform::scaleByMult(float scale)
{
    this->scale *= scale;
}

void Transform::translateBy(Eigen::Vector3f position)
{
    this->translate += position;
}

void Transform::rotateBy(Eigen::Vector3f rotate)
{
    this->rotate += rotate;
}

