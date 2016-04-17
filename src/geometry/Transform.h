//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_TRANSFORM_H
#define RAYTRACER473_TRANSFORM_H


#include <Eigen/Dense>

class Transform
{
    //todo quaterions for the rotate variable
private:
    Eigen::Vector3f translate,rotate,scale;
    Eigen::Matrix4f transform;
public:
    Transform();
    Transform(Eigen::Vector3f translate, Eigen::Vector3f rotate, Eigen::Vector3f scale);

    const Eigen::Vector3f & getTranslate() const;
    const Eigen::Vector3f & getRotate() const;
    const Eigen::Vector3f & getScale() const;

    void setTranslate(const Eigen::Vector3f &translate);
    void setRotate(const Eigen::Vector3f &rotate);
    void setScale(const Eigen::Vector3f &scale);

    void scaleBy(Eigen::Vector3f scale);
    void scaleBy(float scale);
    void scaleByMult(Eigen::Vector3f scale);
    void scaleByMult(float scale);


    void translateBy(Eigen::Vector3f position);
    void rotateBy(Eigen::Vector3f scale);

};


#endif //RAYTRACER473_TRANSFORM_H
