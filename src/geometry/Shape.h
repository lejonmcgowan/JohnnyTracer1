//
// Created by lejonmcgowan on 4/7/16.
//

#ifndef RAYTRACER473_SHAPE_H
#define RAYTRACER473_SHAPE_H

#include "Ray.h"
#include "HitData.h"
#include "Material.h"
#include "Transform.h"
#include "Color.h"
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

class Shape
{
protected:
    Color color;
protected:
    Material material;
    Transform transform;
    Eigen::Matrix4f inverseTransform;
public:
    virtual bool hit(const Ray& ray, HitData& shadeData) = 0;
    virtual bool hit(const Ray& ray, float& t) = 0;

    Material& getMaterial();
    Transform& getTransform();
    Color& getColor();
    void setMaterial(const Material& material);
    void setTransform(const Transform& transform);
    void setColor(Color color);
    void initTransformation();
    bool isTransform() { return transform.isTransform(); }
    const Eigen::Matrix4f& getInvMat() { return inverseTransform; }
    virtual ~Shape();

    Ray toObjectSpace(const Ray& ray);
};


#endif //RAYTRACER473_SHAPE_H
