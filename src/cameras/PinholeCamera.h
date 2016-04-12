//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_PINHOLECAMERA_H
#define RAYTRACER473_PINHOLECAMERA_H


#include "Camera.h"

class PinholeCamera: public Camera
{
private:

public:
    virtual void renderScene(Scene &scene) override;
};


#endif //RAYTRACER473_PINHOLECAMERA_H
