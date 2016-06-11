//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_TRANSFORM_H
#define RAYTRACER473_TRANSFORM_H


#include <Eigen/Dense>
#include <geometry/Ray.h>
#include <vector>
class Transform
{
    //todo quaterions for the rotate variable
private:
    Eigen::Matrix4f transform;
    bool identity;
    bool dirty;
    void setDirty();
    std::vector<Eigen::Affine3f> transformations;
public:
    Transform();

    void addTranslate(const Eigen::Vector3f& translate);
    void addRotate(const Eigen::Vector3f& rotate);
    void addScale(const Eigen::Vector3f& scale);

    bool isTransform() { return !identity; }
    Eigen::Matrix4f getTransformMatrix();
    Ray transformRay(const Ray& ray);
    Eigen::Vector3f transformPoint(const Eigen::Vector3f& point);
};


#endif //RAYTRACER473_TRANSFORM_H
