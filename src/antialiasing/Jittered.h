//
// Created by lejonmcgowan on 5/15/16.
//

#ifndef RAYTRACER473_JITTERED_H
#define RAYTRACER473_JITTERED_H


#include "Sampler.h"
class Jittered: public Sampler
{
public:

    virtual void makeSamples() override;
    virtual void mapToHemisphere() override;

};


#endif //RAYTRACER473_JITTERED_H
