//
// Created by lejonmcgowan on 4/16/16.
//
#include <lights/Light.h>
#include <cameras/scenes/Scene.h>
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

Eigen::Vector3f Material::getRefractedColor(HitData& data, bool& resultRefract)
{
    Color color;
    bool stillRefract = data.material->refraction == 1;
    float influence = (data.material)->ambient.f;
    Ray recurseRay;
    Material *inMat = data.currentMaterial;
    Material *outMat = this;

    //if we're in the same material, we exit it to the default space (should pop off some stack)
    if (index == data.currentMaterial->index)
    {
        assert(data.previousMaterial);
        inMat = this;
        outMat = data.previousMaterial;
    }

    recurseRay.origin = data.hitPoint;

    Eigen::Vector3f incidentVector = data.ray.direction.normalized();
    Eigen::Vector3f origin = inMat->ior * (incidentVector - data
        .normal * (incidentVector.dot(data.normal))) / outMat->ior;

    float rootNumerator = inMat->ior * inMat->ior *
        (1 - std::pow(incidentVector.dot(data.normal), 2));
    float rootDenominator = outMat->ior * outMat->ior;
    float root = std::sqrt(1 - rootNumerator / rootDenominator);
    recurseRay.direction = (origin - data.normal * root).normalized();

    //move the origin slight past hitpoint
    recurseRay.origin += recurseRay.direction * 2 * Constants::EPSILON;
    Ray slightlyOffsetRecurse(recurseRay.origin + recurseRay.direction * 2 * Constants::EPSILON, recurseRay.direction);
    auto recurseData = data.scene->castRay(slightlyOffsetRecurse, data.depth - 1);

    recurseData.previousMaterial = data.currentMaterial;
    recurseData.currentMaterial = this;
    stillRefract = recurseData.hit;
    //shade if the recurse ray hit anything
    if (stillRefract)
    {
        color.addColor(influence * recurseData.material->shade(recurseData).getRGB());
    }
    //make sure any ray that is more than one level in is a refraction ray,
    //and mult in the filter compliment to the the dffuse
    if (data.depth < SceneContext::numBounces)
    {
        data.bounceInfo.back().type = "refraction";
        data.bounceInfo.back().diffuse = Color((1 - ambient.f) * diffuse.getRGB());
    }
    //append result from recusive data to this one
    data.bounceInfo.insert(data.bounceInfo.end(), recurseData.bounceInfo.begin(), recurseData
        .bounceInfo.end());
    //one last check for if the ray should continue to recurse
    if (recurseData.material)
        influence *= recurseData.material->ambient.f;
    stillRefract &= influence > Constants::EPSILON;
    resultRefract = stillRefract;
    return color.getRGB();
}

Color Material::shade(HitData& data)
{
    //assert(index != -1);
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
        shadowed = SceneContext::shadows ? light->inShadow(lightDir, data) : false;
        //current material
        if(!shadowed)
        {
            //specular stuff
            Eigen::Vector3f
                halfVector = ((data.ray.origin - data.hitPoint).normalized() + (light->getLocation()
                - data.hitPoint).normalized()).normalized();
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
        bounceData.diffuse = Color(diffuse.getRGB() * (1 - ambient.f));
        bounceData.specular = specular;
        bounceData.type = "primary";
        data.bounceInfo.push_back(bounceData);
        //reflections
        if (data.material->reflection > Constants::EPSILON && data.depth > 0)
        {
            lightColor += getReflectedColor(data);
        }
        if (data.material->reflection > Constants::EPSILON && data.depth == 0)
        {
            lightColor = Color().getRGB();
            totalColor = Color();
            data.bounceInfo.back().type = "reflection";
            data.bounceInfo.back().diffuse = Color((1 - reflection) * diffuse.getRGB());
        }
        //refractions
        bool stillRefract;
        if (data.material->refraction == 1 && data.material->ambient.f > Constants::EPSILON && data
            .depth > 0)
        {
            lightColor += getRefractedColor(data, stillRefract);
        }
        else if (data.material->refraction == 1 && !stillRefract)
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



