//
// Created by lejonmcgowan on 4/10/16.
//

#include <geometry/Ray.h>
#include "PinholeCamera.h"
#include "Scene.h"

void PinholeCamera::renderScene(Scene& scene)
{
    Ray	ray;

    ray.origin = position;

    for (int r = 0; r < scene.width; r++)
        for (int c = 0; c < scene.height; c++)
        {
            Eigen::Vector3i color;

            auto data = scene.castRay(ray);
            if(data.hit)
                color = 255 * data.color.cast<int>();
            else
                color = scene.backgroundColor;

            scene.pushPixel(color);
        }
}

