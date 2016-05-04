//
// Created by lejonmcgowan on 4/14/16.
//

#include <util/MathUtils.h>
#include "Triangle.h"
using namespace Eigen;

Triangle::Triangle(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c)
    : a(a), b(b), c(c)
{

}
/*solve for variables [t,b1,b2] w/:
    1/(s1.dot(e1)) * (s2.dot(e2),s1.dot(s),s2.dot(ray.direction()))

    notation note:
    s = ray.origin - a
    s1 = ray.direction.cross(e2)
    s2 = s.cross(e1)
    b1,b2: barycentric coordinates
*/
bool Triangle::hit(const Ray& ray, HitData& hitData)
{
    /*First, calc the convienience variable s1, and use
     * to find denominator*/
    float b1, b2;
    hitData.ray = ray;
    //convienence e's and s's for calculations
    Vector3f e1(b - a);
    Vector3f e2(c - a);
    Vector3f s(ray.origin - a);
    Vector3f s1 = ray.direction.cross(e2);
    Vector3f s2 = s.cross(e1);
    float s1DotE1 = s1.dot(e1);

    //short circuit check one
    if (MathHelper::equalsEpsilon(s1DotE1, 0, 1e-6))
        return false;

    /*now, calculate b1*/
    b1 = s1.dot(s) / s1DotE1;
    //short circut check two: is bary in bounds
    if (b1 < 0 || b1 > 1)
        return false;
    /*Same for b2. Also check for if the sum exceeds 1*/
    b2 = ray.direction.dot(s2) / s1DotE1;
    if (b2 < 0 || b1 + b2 > 1)
        return false;
    /*calc time collided*/
    hitData.timeCollided = e2.dot(s2) / s1DotE1;
    if (hitData.timeCollided < Constants::EPSILON)
        return false;
    hitData.hit = true;
    /*find intersection point*/
    hitData.hitPoint = ray.origin + ray.direction * hitData.timeCollided;
    hitData.color = color;
    hitData.material = &material;
    hitData.normal = e1.cross(e2).normalized();
    return true;
}

bool Triangle::hit(const Ray& ray, float& t)
{
    /*First, calc the convienience variable s1, and use
     * to find denominator*/
    float b1, b2;
    //convienence e's and s's for calculations
    Vector3f e1(b - a);
    Vector3f e2(c - a);
    Vector3f s(ray.origin - a);
    Vector3f s1 = ray.direction.cross(e2);
    Vector3f s2 = s.cross(e1);
    float s1DotE1 = s1.dot(e1);

    //short circuit check one
    if (MathHelper::equalsEpsilon(s1DotE1, 0, 1e-6))
        return false;

    /*now, calculate b1*/
    b1 = s1.dot(s) / s1DotE1;
    //short circut check two: is bary in bounds
    if (b1 < 0 || b1 > 1)
        return false;
    /*Same for b2*/
    b2 = ray.direction.dot(s2) / s1DotE1;
    if (b2 < 0 || b1 + b2 > 1)
        return false;
    /*calc time collided*/
    t = e2.dot(s2) / s1DotE1;
    return t > Constants::EPSILON;
}
