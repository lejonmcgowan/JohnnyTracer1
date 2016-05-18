//
// Created by lejonmcgowan on 4/16/16.
//

#include "Transform.h"
#include <Eigen/Geometry>
#include <util/MathUtils.h>
Transform::Transform()
{

}

void Transform::addTranslate(const Eigen::Vector3f& translate)
{
    Eigen::Affine3f affineTranslate(Eigen::Translation3f(translate[0], translate[1], translate[2]));
    transformations.push_back(affineTranslate);
    setDirty();
}

void Transform::addRotate(const Eigen::Vector3f& rotate)
{
    Eigen::Affine3f rotx(Eigen::AngleAxisf(MathHelper::toRadians(rotate[0]), Eigen::Vector3f(1, 0, 0)));
    Eigen::Affine3f roty(Eigen::AngleAxisf(MathHelper::toRadians(rotate[1]), Eigen::Vector3f(0, 1, 0)));
    Eigen::Affine3f rotz(Eigen::AngleAxisf(MathHelper::toRadians(rotate[2]), Eigen::Vector3f(0, 0, 1)));
    transformations.push_back(rotz * roty * rotx);
    setDirty();
}

void Transform::addScale(const Eigen::Vector3f& scale)
{
    Eigen::Affine3f affineScale(Eigen::Scaling(scale[0], scale[1], scale[2]));
    transformations.push_back(affineScale);
    setDirty();
}

Eigen::Matrix4f Transform::getTransformMatrix()
{
    if (dirty)
    {
        Eigen::Matrix4f finalTransform;
        finalTransform.setIdentity();
        for (auto currentTransform: transformations)
            finalTransform = currentTransform.matrix() * finalTransform;
        transform = finalTransform;
    }
    dirty = false;
    return transform;
}

void Transform::setDirty()
{
    dirty = true;
    identity = false;
}

Ray Transform::transformRay(const Ray& ray)
{
    Ray transformRay;
    Eigen::Vector4f vectorO, vectorD;
    vectorO << ray.origin[0], ray.origin[1], ray.origin[2], 1;
    vectorD << ray.direction[0], ray.direction[1], ray.direction[2], 0;

    vectorO = getTransformMatrix() * vectorO;
    vectorD = getTransformMatrix() * vectorD;

    transformRay.origin << vectorO[0], vectorO[1], vectorO[2];
    transformRay.direction << vectorD[0], vectorD[1], vectorD[2];
    transformRay.direction.normalize();

    return transformRay;
}

Eigen::Vector3f Transform::transformPoint(const Eigen::Vector3f& point)
{
    Eigen::Vector3f transformPoint;
    Eigen::Vector4f vector;
    vector << point[0], point[1], point[2], 1;


    vector = getTransformMatrix() * vector;

    transformPoint << vector[0], vector[1], vector[2];

    return transformPoint;
}
