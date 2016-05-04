//
// Created by lejonmcgowan on 4/16/16.
//
#include <lights/Light.h>
#include <cameras/Scene.h>
#include <util/Constants.h>
#include <util/SceneContext.h>
#include "Material.h"

Eigen::Vector3f getReflectedColor(HitData& data)
{
    Color color;
    bool stillReflect = data.material->reflection > Constants::EPSILON;
    float influence = (data.material)->reflection;
    Ray recurseRay;

    recurseRay.origin = data.hitPoint;
    Eigen::Vector3f d = data.hitPoint - data.ray.origin;
    d.normalize();
    recurseRay.direction = d - (2 * data.normal.dot(d)) *
        data.normal;
    auto recurseData = data.scene->castRay(recurseRay, data.depth - 1);
    stillReflect = recurseData.hit;
    if (stillReflect)
    {
        color.addColor(influence * recurseData.material->shade(recurseData).getRGB());
    }
    if (recurseData.material)
        influence *= recurseData.material->reflection;
    stillReflect &= influence > 0;

    return color.getRGB();
}

Eigen::Vector3f Material::getRefractedColor(HitData& data)
{
    Color color;
    return color.getRGB();
}

Color Material::shade(HitData& data)
{
    Color totalColor,ambientColor;
    Eigen::Vector3f lightColor;
    lightColor.setZero();
    ambientColor = ambient;
    totalColor.addColor(ambientColor.getRGB());
    const Scene* scene = data.scene;
    for(auto light: scene->getLights())
    {
        Eigen::Vector3f inAngle = light->getDirection(data);
        bool shadowed = false;
        Ray lightDir(data.hitPoint, inAngle);
        data.shadowRay = lightDir;
        shadowed = light->inShadow(lightDir, data);
        //current material
        if(!shadowed)
        {
            //specular stuff
            Eigen::Vector3f
                halfVector = (data.ray.direction + light->getTransform().getTranslate() -
                data.hitPoint).normalized();
            float hdotn = halfVector.dot(data.normal);
            hdotn = std::max(hdotn,0.0f);
            Eigen::Vector3f specRGB = specularPercent * (data.color.getRGB().array() *
                light->getColor().getRGB().array()) * std::pow
                (hdotn, 1 / roughness);
            specular.setRGB(specRGB);
            //diffuse stuff
            float ndotl = data.normal.dot(inAngle);
            ndotl = std::max(ndotl,0.0f);
            Eigen::Vector3f diffRGB = diffusePercent * (data.color
                .getRGB().array() * light->getColor().getRGB().array()) * ndotl;
            diffuse.setRGB(diffRGB);
            //combine
            lightColor = (1 - data.material->reflection) * (diffRGB + specRGB);
        }
        else
        {
            diffuse.setRGB(0, 0, 0);
            specular.setRGB(0, 0, 0);
        }
        //reflections
        if (data.material->reflection > Constants::EPSILON && data.depth > 0)
            lightColor += getReflectedColor(data);
        else if (data.material->reflection > Constants::EPSILON && data.depth == 0)
        {
            lightColor = Color().getRGB();
            totalColor = Color();
        }
        if (data.material->refraction > Constants::EPSILON && data.depth > 0)
        {
            lightColor += getRefractedColor(data);
        }
        else if (data.material->refraction > Constants::EPSILON && data.depth == 0)
        {
            lightColor = Color().getRGB();
            totalColor = Color();
        }

        totalColor.addColor(lightColor);

    }
    return totalColor;
}



