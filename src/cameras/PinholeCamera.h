//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_PINHOLECAMERA_H
#define RAYTRACER473_PINHOLECAMERA_H


#include "Camera.h"

class PinholeCamera: public Camera
{
private:
    int focalLength;
    bool initialized = false;
public:
    virtual void renderScene(Scene &scene) override;

    PinholeCamera(Eigen::Vector3f position, Eigen::Vector3f lookat, Eigen::Vector3f up, int focalLength = 1);

    PinholeCamera(const PinholeCamera &camera);

    Ray getProjRay(float r, float c);

    virtual ~PinholeCamera() override;

};


#endif //RAYTRACER473_PINHOLECAMERA_H


