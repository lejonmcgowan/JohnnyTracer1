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
public:


protected:
    Material material;
    Transform transform;
public:
    virtual bool hit(const Ray& ray, HitData& shadeData) = 0;

    Material& getMaterial();
    const Transform& getTransform();
    Color& getColor();
    void setMaterial(const Material& material);
    void setTransform(const Transform& transform);
    void setColor(Color color);
    virtual ~Shape();
};


#endif //RAYTRACER473_SHAPE_H
