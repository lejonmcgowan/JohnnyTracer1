//
// Created by lejonmcgowan on 4/10/16.
//


#include <util/SceneContext.h>
#include <util/MathUtils.h>
#include <geometry/HitData.h>
#include "PinholeCamera.h"
#include "Scene.h"

using namespace Eigen;

void PinholeCamera::renderScene(Scene& scene)
{
    if (!initialized)
    {
        computeBasis();
        initialized = true;
    }
    Ray	ray;

    ray.origin = position;

    for (int r = 0; r < SceneContext::windowDims[1]; r++)
        for (int c = 0; c < SceneContext::windowDims[0]; c++)
        {
            //calc direction
            Vector2f mappedCoords = MathHelper::mapCoords(Vector2f(c + 0.5f, r + 0.5f),
                                                          Vector4f(0,SceneContext::width(),
                                                                   0,SceneContext::height()),
                                                          Vector4f(-SceneContext::aspect / 2.0f,
                                                                   SceneContext::aspect / 2.0f,
                                                                   -0.5, 0.5));

            Vector3f finalResult =
                -focalLength * wBasis + mappedCoords[0] * uBasis + mappedCoords[1] * vBasis;
            finalResult.normalize();
            ray.direction = finalResult;

            Color color;

            auto data = scene.castRay(ray, SceneContext::numReflections);
            if(data.hit)
            {
                color = data.material->shade(data);
            }
            else
            {
                color = SceneContext::backgroundColor;
            }

            scene.pushPixel(color);
        }
}

PinholeCamera::PinholeCamera(Camera::vec3 position, Camera::vec3 lookat, Camera::vec3 up, int focalLength) :
        Camera(position, lookat,up),
        focalLength(focalLength)
{

}

PinholeCamera::PinholeCamera(const PinholeCamera &camera) : Camera(camera)
{
    this->focalLength = camera.focalLength;
}

PinholeCamera::~PinholeCamera()
{

}

Ray PinholeCamera::getProjRay(int r, int c)
{
    if (!initialized)
    {
        computeBasis();
        initialized = true;
    }
    //calc direction
    Vector2f mappedCoords = MathHelper::mapCoords(Vector2f(r + 0.5f, c + 0.5f),
                                                  Vector4f(0, SceneContext::width(),
                                                           0, SceneContext::height()),
                                                  Vector4f(-SceneContext::aspect / 2.0f,
                                                           SceneContext::aspect / 2.0f,
                                                           -0.5, 0.5));

    Vector3f finalResult =
        -focalLength * wBasis + mappedCoords[0] * uBasis + mappedCoords[1] * vBasis;
    return Ray(position, finalResult.normalized());
}




