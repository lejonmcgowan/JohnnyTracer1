//
// Created by lejonmcgowan on 4/16/16.
//
#include <lights/Light.h>
#include <cameras/Scene.h>
#include <util/Constants.h>
#include <util/SceneContext.h>
#include "Material.h"

Eigen::Vector3f Material::getReflectedColor(HitData& data)
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
    if (data.depth < SceneContext::numBounces)
    {
        data.bounceInfo.back().type = "reflection";
        data.bounceInfo.back().diffuse = Color((1 - reflection) * diffuse.getRGB());
    }
    data.bounceInfo.insert(data.bounceInfo.end(), recurseData.bounceInfo.begin(), recurseData
        .bounceInfo.end());
    if (recurseData.material)
        influence *= recurseData.material->reflection;
    stillReflect &= influence > 0;

    return color.getRGB();
}

Eigen::Vector3f Material::getRefractedColor(HitData& data)
{
    Color color;
    bool stillRefract = data.material->refraction == 1;
    float influence = (data.material)->ambient.f;
    Ray recurseRay;

    recurseRay.origin = data.hitPoint;
    Eigen::Vector3f incidentVector = data.timeCollided * data.ray.direction;
    Eigen::Vector3f origin = data.material->ior * (incidentVector - data
        .normal * (incidentVector.dot(data.normal))) / ior;
    float root = std::sqrt(1 - ((data.material->ior) * (data.material->ior) * (1 -
        std::pow(incidentVector.dot(data.normal), 2)) / (ior * ior)));
    recurseRay.direction = (origin - data.normal * root).normalized();
    auto recurseData = data.scene->castRay(recurseRay, data.depth - 1);

    stillRefract = recurseData.hit;
    if (stillRefract)
    {
        color.addColor(influence * recurseData.material->shade(recurseData).getRGB());
    }
    if (data.depth < SceneContext::numBounces)
        data.bounceInfo.back().type = "refraction";
    data.bounceInfo.insert(data.bounceInfo.end(), recurseData.bounceInfo.begin(), recurseData
        .bounceInfo.end());
    if (recurseData.material)
        influence *= recurseData.material->reflection;
    stillRefract &= influence > 0;

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
                halfVector = (data.ray.origin - data.hitPoint + light->getLocation() -
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
            lightColor = (1 - data.material->reflection - ambient.f) * (diffRGB + specRGB);
        }
        else
        {
            diffuse.setRGB(0, 0, 0);
            specular.setRGB(0, 0, 0);
        }
        BounceData bounceData;
        bounceData.timeCollided = data.timeCollided;
        bounceData.bounceIndex = SceneContext::numBounces - data.depth;
        bounceData.hitPoint = data.hitPoint;
        bounceData.ray = data.ray;
        bounceData.ambient = ambient;
        bounceData.diffuse = diffuse;
        bounceData.specular = specular;
        bounceData.type = "primary";
        data.bounceInfo.push_back(bounceData);
        //reflections
        if (data.material->reflection > Constants::EPSILON && data.depth > 0)
        {
            lightColor += getReflectedColor(data);
        }
        else if (data.material->reflection > Constants::EPSILON && data.depth == 0)
        {
            lightColor = Color().getRGB();
            totalColor = Color();
            data.bounceInfo.back().type = "reflection";
            data.bounceInfo.back().diffuse = Color((1 - reflection) * diffuse.getRGB());
        }
        //refractions
        if (data.material->refraction == 1 && data.material->ambient.f > Constants::EPSILON && data
            .depth > 0)
        {
            lightColor += getRefractedColor(data);
        }
        else if (data.material->refraction == 1 && data.depth == 0)
        {
            lightColor = Color().getRGB();
            totalColor = Color();
            data.bounceInfo.back().type = "refraction";
            data.bounceInfo.back().diffuse = Color((1 - ambient.f) * diffuse.getRGB());
        }

        totalColor.addColor(lightColor);

    }
    return totalColor;
}



