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
    bool initialized;
public:
    virtual void renderScene(Scene &scene) override;

    PinholeCamera(Camera::vec3 position, Camera::vec3 lookat, Camera::vec3 up,int focalLength = 1);

    PinholeCamera(const PinholeCamera &camera);

    Ray getProjRay(int r, int c);

    virtual ~PinholeCamera() override;

};


#endif //RAYTRACER473_PINHOLECAMERA_H


