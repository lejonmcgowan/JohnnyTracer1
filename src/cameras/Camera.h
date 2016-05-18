//
// Created by lejonmcgowan on 4/10/16.
//

#ifndef RAYTRACER473_CAMERA_H
#define RAYTRACER473_CAMERA_H


#include <Eigen/Dense>
#include <geometry/Ray.h>
#include <antialiasing/Sampler.h>
#include <memory>

class Scene;
class Camera
{
protected:
    // orthonormal basis vectors
    Eigen::Vector3f uBasis, vBasis, wBasis;
    Eigen::Vector3f position;
    Eigen::Vector3f lookat;
    Eigen::Vector3f up;
    void computeBasis(void);
    std::shared_ptr<Sampler> sampler;
public:
    Camera(Eigen::Vector3f position = Eigen::Vector3f(0, 0, 0),
           Eigen::Vector3f lookat = Eigen::Vector3f(0, 0, 0),
           Eigen::Vector3f up = Eigen::Vector3f(0, 1, 0));

    //rule of 3
    Camera(const Camera& camera);
    virtual ~Camera(){};
    virtual void init();
    virtual void renderScene(Scene& scene) = 0;
    void setSampler(std::shared_ptr<Sampler> sampler) { this->sampler = sampler; }
};




#endif //RAYTRACER473_CAMERA_H
