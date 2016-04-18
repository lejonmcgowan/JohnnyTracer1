//
// Created by lejonmcgowan on 4/16/16.
//
#include <lights/Light.h>
#include <cameras/Scene.h>
#include "Material.h"



Color Material::shade(HitData data)
{
    Color totalColor,ambientColor;
    ambientColor.setRGB(0.1,0.1,0.1);
    totalColor.addColor(ambientColor.getRGB());
    const Scene* scene = data.scene;
    for(auto light: scene->getLights())
    {
        Eigen::Vector3f inAngle = light->getDirection(data);
        bool shadowed = false;
        Ray ray(data.hitPoint,inAngle);
        shadowed = light->inShadow(ray,data);

        if(!shadowed)
        {
            //specular stuff
            Eigen::Vector3f halfVector = (data.ray.direction + inAngle).normalized();
            float hdotn = halfVector.dot(data.normal);
            hdotn = std::max(hdotn,0.0f);
            Eigen::Vector3f specRGB = Eigen::Vector3f(1.0f,1.0f,1.0f) * std::pow(hdotn, specularexp);
            //diffuse stuff
            float ndotl = data.normal.dot(inAngle);
            ndotl = std::max(ndotl,0.0f);
            Eigen::Vector3f diffRGB =  diffusePercent * data.color.getRGB() * ndotl;

            //combine
            Eigen::Vector3f lightColor = light->getColor().getRGB().array() * (diffRGB +
                specRGB)
                .array();


            totalColor.addColor(lightColor);
        }

    }
    return totalColor;
}

