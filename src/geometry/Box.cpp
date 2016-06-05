//
// Created by lejonmcgowan on 4/14/16.
//

#include <util/Constants.h>
#include "Box.h"

Box::Box(Eigen::Vector3f min, Eigen::Vector3f max)
    : min(min),
      max(max)
{

}

bool Box::hit(const Ray& ray, HitData& hitData)
{
    bool result = hit(ray, hitData.timeCollided);
    if (!result)
        return false;

    //calculate hitpoint
    hitData.hitPoint = ray.origin + ray.direction * hitData.timeCollided;
    //and normals
    const Eigen::Vector3f normals[] = {Eigen::Vector3f(1, 0, 0), Eigen::Vector3f(0, 1, 0), Eigen::Vector3f(0, 0, 1)};
    if (tnearIndex > Constants::EPSILON)
        hitData.normal = normals[tnearIndex];
    else
        hitData.normal = normals[tfarIndex];
    //and the shading stuff
    hitData.color = color;
    hitData.material = &material;

    return result;
}

bool Box::hit(const Ray& ray, float& t)
{
    bool result = true;
    Eigen::Vector3f tmins, tmaxs;
    //calc the tmins and maxs for each orientation
    for (int i = 0; i < 3; i++)
    {
        //to efficently tae into account divide-by-zero directions
        float invDir = 1 / ray.direction[i];
        if (invDir >= 0)
        {
            tmins[i] = (min[i] - ray.origin[i]) * invDir;
            tmaxs[i] = (max[i] - ray.origin[i]) * invDir;
        }
        else
        {
            tmins[i] = (max[i] - ray.origin[i]) * invDir;
            tmaxs[i] = (min[i] - ray.origin[i]) * invDir;
        }
    }
    //now, test if the ray hits at all by checking the mins and maxs

    //x vs. y
    result &= tmins[0] < tmaxs[1];
    result &= tmins[1] < tmaxs[0];
    //x vs. z
    result &= tmins[0] < tmaxs[2];
    result &= tmins[2] < tmaxs[0];
    //y vs. z
    result &= tmins[1] < tmaxs[2];
    result &= tmins[2] < tmaxs[1];

    /*make sure the box collision is in front of the ray.
    we don't care whether we are actually in the box or not (atm, probably should for easier future things,
     so we can test against the max coordinated*/
    result &= tmaxs[0] > Constants::EPSILON;
    result &= tmaxs[1] > Constants::EPSILON;
    result &= tmaxs[2] > Constants::EPSILON;

    //since we're interested in the actual time, find the  smallest positive time and return it
    if (result)
    {
        t = -1;
        tnearIndex = 0;
        for (int i = 0; i < 3; i++)
        {
            if (tmins[i] > Constants::EPSILON && (tmins[i] < t || t < 0))
            {
                t = tmins[i];
                tnearIndex = i;
            }
        }
        tfarIndex = tmaxs[0] < tmaxs[1] ? (tmaxs[0] < tmaxs[2] ? tmaxs[0] : tmaxs[2])
                                        : (tmaxs[1] < tmaxs[2] ? tmaxs[1] : tmaxs[2]);
        //if still negative, we know at this point that all the tmaxs are good. return the smallest of tmax
        if (t < 0)
            t = tfarIndex;
        //lazy so let's see which index this equals seprately
        if (tfarIndex == tmaxs[0])
            tfarIndex = 0;
        else if (tfarIndex == tmaxs[1])
            tfarIndex = 1;
        else
            tfarIndex = 2;

    }
    return result;
}
std::shared_ptr<BoundingBox> Box::getBBox()
{
    if (!bbox)
    {
        bbox = std::make_shared<BoundingBox>(min, max);
        Shape::getBBox();
    }
    return bbox;
}