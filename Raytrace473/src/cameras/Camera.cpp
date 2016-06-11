//
// Created by lejonmcgowan on 4/10/16.
//

#include "Camera.h"

Camera::Camera(const Camera &camera)
{
    position = camera.position;
    lookat = camera.lookat;
    up = camera.up;
}

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f lookat, Eigen::Vector3f up)
    :
        position(position),
        lookat(lookat),
        up(up)
{

}


/*Camera Camera::operator=(const Camera &camera)
{
    lookat = camera.lookat;
    up = camera.up;
    position = camera.position;
    
    return *this;
}*/

void Camera::computeBasis()
{
    wBasis = (position - lookat).normalized();
    uBasis = up.cross(wBasis).normalized();
    vBasis = wBasis.cross(uBasis);
    vBasis *= -1;
}

void Camera::init()
{
    if (sampler)
        sampler->makeSamples();
}