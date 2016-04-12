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
    const Eigen::Vector3f& result = lookat - position;
    forwardBasis = result.normalized();
    upBasis = up.cross(forwardBasis);
    rightBasis = upBasis.cross(forwardBasis);
}

