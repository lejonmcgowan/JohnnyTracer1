//
// Created by lejonmcgowan on 5/15/16.
//

#ifndef RAYTRACER473_SAMPLER_H
#define RAYTRACER473_SAMPLER_H


#include <Eigen/Dense>
#include <util/SceneContext.h>
class Sampler
{
private:
    int count;
public:
    virtual void makeSamples() = 0;
    virtual Eigen::Vector2f getSample()
    {
        return samplePoints[count++ % (NUM_SETS * SceneContext::numSamples)];
    }
protected:
    static int NUM_SETS;
    std::vector<Eigen::Vector2f> samplePoints;

};


#endif //RAYTRACER473_SAMPLER_H
