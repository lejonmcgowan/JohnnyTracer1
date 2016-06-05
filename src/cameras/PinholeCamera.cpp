//
// Created by lejonmcgowan on 4/10/16.
//


#include <util/SceneContext.h>
#include <util/MathUtils.h>
#include <geometry/HitData.h>
#include "PinholeCamera.h"
#include "cameras/scenes/Scene.h"

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
            Color color;
            if (sampler && SceneContext::numSamples > 1)
            {
                std::vector<Color> colors;
                for (int sample = 0; sample < SceneContext::numSamples; sample++)
                {
                    Eigen::Vector2f currentSample = sampler->getSample();
                    ray = getProjRay(c + currentSample[0], r + currentSample[1]);

                    auto data = scene.castRay(ray, SceneContext::numBounces);
                    if (data.hit)
                    {
                        colors.push_back(data.material->shade(data));
                    }
                    else
                    {
                        colors.push_back(SceneContext::backgroundColor);
                    }
                }


                color = Color::averageColors(colors);
            }
            else
            {
                ray = getProjRay(c, r);

                auto data = scene.castRay(ray, SceneContext::numBounces);
                if (data.hit)
                {
                    color = data.material->shade(data);
                }
                else
                {
                    color = SceneContext::backgroundColor;
                }
            }

            scene.pushPixel(color);
        }
}

PinholeCamera::PinholeCamera(Eigen::Vector3f position, Eigen::Vector3f lookat, Eigen::Vector3f up, int focalLength)
    :
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

Ray PinholeCamera::getProjRay(float r, float c)
{
    Ray ray;
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

    Vector3f finalResult;
    finalResult = -focalLength * wBasis + mappedCoords[0] * uBasis + mappedCoords[1] * vBasis;
    finalResult.normalize();
    ray.origin = position;
    ray.direction = finalResult;
    return ray;
}
