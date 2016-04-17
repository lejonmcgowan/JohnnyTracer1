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

Camera::Camera(Camera::vec3 position, Camera::vec3 lookat, Camera::vec3 up):
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

