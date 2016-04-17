//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_CAMERA_H
#define RAYTRACER473_CAMERA_H


#include <Eigen/Dense>

class Scene;


class Camera
{
protected:
    typedef Eigen::Vector3f vec3;
    // orthonormal basis vectors
    vec3 upBasis, rightBasis, forwardBasis;
    vec3 position;
    vec3 lookat;
    vec3 up;
    void computeBasis(void);
public:
    Camera(vec3 position = vec3(),vec3 lookat = vec3(), vec3 up = vec3(0,1,0));

    //rule of 3
    Camera(const Camera& camera);
    virtual ~Camera(){};
    //Camera operator=(const Camera& camera);

    virtual void renderScene(Scene& scene) = 0;
};




#endif //RAYTRACER473_CAMERA_H
