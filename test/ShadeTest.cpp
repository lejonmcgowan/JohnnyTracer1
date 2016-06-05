//
// Created by lejonmcgowan on 4/21/16.
//

#include <include/gtest/gtest.h>
#include <util/MathUtils.h>
#include <geometry/Plane.h>
#include "../src/util/SceneContext.h"
#include "cameras/scenes/Scene.h"
#include "../src/fileparsing/POVParser.h"
#include "../src/geometry/Sphere.h"
#include "../src/cameras/PinholeCamera.h"

TEST(TestShading, shading1)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/simple.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());

    //ambient tests
    Color sphereAmbient(sphere.getMaterial().ambient);
    EXPECT_EQ(Color(51, 0, 51, true), sphereAmbient);

    Color planeAmbient(plane.getMaterial().ambient);
    EXPECT_EQ(Color(20, 20, 82, true), planeAmbient);

    HitData hitdata(&scene);
    hitdata.hit = false;
    hitdata.ray = camera->getProjRay(120, 480 - 120 - 1);
    plane.hit(hitdata.ray, hitdata);
    EXPECT_TRUE(hitdata.hit);
    bool timeCollidedEquals = MathHelper::equalsEpsilon(hitdata.timeCollided, 17.8533);
    EXPECT_TRUE(timeCollidedEquals);
    plane.getMaterial().shade(hitdata);

    EXPECT_EQ(Color(37, 37, 147, true), plane.getMaterial().diffuse);
    EXPECT_EQ(Color(0, 0, 0, true), plane.getMaterial().specular);
    Eigen::Vector3f correctShadowDirection(-0.539311290, 0.601018608, 0.589847445);
    bool feelerCompare =
        MathHelper::equalsEpsilon(correctShadowDirection, hitdata.shadowRay.direction);
    EXPECT_TRUE(feelerCompare);

    hitdata.hit = false;
    hitdata.ray = camera->getProjRay(295, 480 - 265 - 1);
    sphere.hit(hitdata.ray, hitdata);
    EXPECT_TRUE(hitdata.hit);
    bool timeCollided2Equals = MathHelper::equalsEpsilon(hitdata.timeCollided, 12.247);
    EXPECT_TRUE(timeCollided2Equals);
    sphere.getMaterial().shade(hitdata);

    EXPECT_EQ(Color(135, 0, 135, true), sphere.getMaterial().diffuse);
    EXPECT_EQ(Color(112, 0, 112, true), sphere.getMaterial().specular);
    correctShadowDirection = Eigen::Vector3f(-0.579651773, 0.579503298, 0.572869658);
    feelerCompare = MathHelper::equalsEpsilon(correctShadowDirection, hitdata.shadowRay.direction);
    EXPECT_TRUE(feelerCompare);

    hitdata.hit = false;
    hitdata.ray = camera->getProjRay(420, 480 - 130 - 1);
    plane.hit(hitdata.ray, hitdata);
    EXPECT_TRUE(hitdata.hit);
    bool timeCollided3Equals = MathHelper::equalsEpsilon(hitdata.timeCollided, 18.3556);
    EXPECT_TRUE(timeCollided3Equals);
    plane.getMaterial().shade(hitdata);

    EXPECT_EQ(Color(0, 0, 0, true), plane.getMaterial().diffuse);
    EXPECT_EQ(Color(0, 0, 0, true), plane.getMaterial().specular);
    correctShadowDirection = Eigen::Vector3f(-0.576993406, 0.578823268, 0.576231062);
    feelerCompare = MathHelper::equalsEpsilon(correctShadowDirection, hitdata.shadowRay.direction);
    EXPECT_TRUE(feelerCompare);
    /**
     * (Diffuse plane)
        Pixel: [120, 120] Ray: {0 0 14} -> {-0.374038 -0.224048 -0.899943} T=17.8533
        Ambient: (20, 20, 82) Diffuse: (37, 37, 147) Specular: (0, 0, 0)
        Feeler: {-0.539311290 0.601018608 0.589847445}

        (Specular highlight on sphere)
        Pixel: [295, 265] Ray: {0 0 14} -> {-0.0509036 0.0529814 -0.997297} T=12.247
        Ambient: (51, 0, 51) Diffuse: (135, 0, 135) Specular: (112, 0, 112)
        Feeler: {-0.579651773 0.579503298 0.572869658}

        (Shadow)
        Pixel: [420, 130] Ray: {0 0 14} -> {0.200006 -0.217917 -0.955254} T=18.3556
        Ambient: (20, 20, 82) Diffuse: (0, 0, 0) Specular: (0, 0, 0)
        Feeler: {-0.576993406 0.578823268 0.576231062}
     */
}