//
// Created by lejonmcgowan on 5/10/16.
//

#include <util/SceneContext.h>
#include <fileparsing/POVParser.h>
#include <include/gtest/gtest.h>
#include <cameras/PinholeCamera.h>
#include <util/MathUtils.h>
/**
 * Reflection on simple_reflect3

Pixel: [320, 145] Ray: {0 0 14} -> {0.00102203 -0.193167 -0.981165} T=12.4377 Color: (255, 255, 222)
----
Iteration type: Primary
Ray: {0 0 14} -> {0.00102203 -0.193167 -0.981165}
Ambient: 0.4, 0.368, 0.204
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Reflection
Ray: {0.0127117 -2.40256 1.79654} -> {0.00469034 -0.88649 -0.462724}
Ambient: 0.116, 0.1, 0.196
Diffuse: 0.0206799, 0.0178275, 0.0349419
Specular: 0, 0, 0
----
Iteration type: Reflection
Ray: {0.0211636 -4 0.962719} -> {0.00469034 0.88649 -0.462724}
Ambient: 0.4, 0.368, 0.204
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Reflection
Ray: {0.0266152 -2.96964 0.424897} -> {0.0214227 -0.980449 -0.195602}
Ambient: 0.116, 0.1, 0.196
Diffuse: 0.0206283, 0.017783, 0.0348548
Specular: 0, 0, 0
----
Iteration type: Reflection
Ray: {0.0491284 -4 0.219338} -> {0.0214227 0.980449 -0.195602}
Ambient: 0.4, 0.368, 0.204
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Reflection
Ray: {0.070998, -2.9991, 0.0196561} -> {0.067852, -0.980816, -0.182747}
Ambient: 0.116, 0.1, 0.196
Diffuse: 0.0205964, 0.0177555, 0.0348009
Specular: 0, 0, 0

refraction on refract2
 */

//480 - 120 - 1
TEST(BounceTest, reflect3)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/simple_reflect3.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(320, 480 - 145 - 1), SceneContext::numBounces);
    Color finalColor = data.material->shade(data);


    EXPECT_EQ(6, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(255, 255, 222, true), finalColor);
    EXPECT_TRUE(MathHelper::equalsEpsilon(data.timeCollided, 12.4377));
    //get riming information
    /*Iteration type: Primary
        Ray: {0 0 14} -> {0.00102203 -0.193167 -0.981165}
        Ambient: 0.4, 0.368, 0.204
        Diffuse: 0, 0, 0
        Specular: 0, 0, 0*/
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0, 0, 14)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.00102203f,
                                                                                    -0.193167,
                                                                                    -.981165)));
    EXPECT_EQ(Color(0.4, 0.368, 0.204), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);
    /*Iteration type: Reflection
        Ray: {0.0127117 -2.40256 1.79654} -> {0.00469034 -0.88649 -0.462724}
        Ambient: 0.116, 0.1, 0.196
        Diffuse: 0.0206799, 0.0178275, 0.0349419
        Specular: 0, 0, 0*/
    bounceData = data.bounceInfo[1];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0.0127117,
                                                                                 -2.40256,
                                                                                 1.79654)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.00469034,
                                                                                    -0.88649,
                                                                                    -0.462724)));
    EXPECT_EQ(Color(0.116, 0.1, 0.196), bounceData.ambient);
    EXPECT_EQ(Color(0.0206799, 0.0178275, 0.0349419), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("reflection", bounceData.type);
    /*Iteration type: Reflection
        Ray: {0.0211636 -4 0.962719} -> {0.00469034 0.88649 -0.462724}
        Ambient: 0.4, 0.368, 0.204
        Diffuse: 0, 0, 0
        Specular: 0, 0, 0*/
    bounceData = data.bounceInfo[2];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0.0211636,
                                                                                 -4,
                                                                                 0.962719)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.00469034,
                                                                                    0.88649,
                                                                                    -0.462724)));
    EXPECT_EQ(Color(0.4, 0.368, 0.204), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("reflection", bounceData.type);
    /*Iteration type: Reflection
    Ray: {0.0266152 -2.96964 0.424897} -> {0.0214227 -0.980449 -0.195602}
    Ambient: 0.116, 0.1, 0.196
    Diffuse: 0.0206283, 0.017783, 0.0348548
    Specular: 0, 0, 0*/
    bounceData = data.bounceInfo[3];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0.0266152,
                                                                                 -2.96964,
                                                                                 0.424897)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0214227,
                                                                                    -0.980449,
                                                                                    -0.195602)));
    EXPECT_EQ(Color(0.116, 0.1, 0.196), bounceData.ambient);
    EXPECT_EQ(Color(0.0206283, 0.017783, 0.0348548), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("reflection", bounceData.type);
    /*Iteration type: Reflection
    Ray: {0.0491284,-4,0.219338} -> {0.0214227,0.980449,-0.195602}
    Ambient: 0.4, 0.368, 0.204
    Diffuse: 0, 0, 0
    Specular: 0, 0, 0*/
    bounceData = data.bounceInfo[4];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0.0491284,
                                                                                 -4,
                                                                                 0.219338)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0214227,
                                                                                    0.980449,
                                                                                    -0.195602)));
    EXPECT_EQ(Color(0.4, 0.368, 0.204), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("reflection", bounceData.type);
    /*Ray: {0.070998, -2.9991, 0.0196561} -> {0.067852, -0.980816, -0.182747}
        Ambient: 0.116, 0.1, 0.196
        Diffuse: 0.0205964, 0.0177555, 0.0348009
        Specular: 0, 0, 0*/
    bounceData = data.bounceInfo[5];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0.070998,
                                                                                 -2.9991,
                                                                                 0.0196561)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.067852,
                                                                                    -0.980816,
                                                                                    -0.182747)));
    EXPECT_EQ(Color(0.116, 0.1, 0.196), bounceData.ambient);
    EXPECT_EQ(Color(0.0205964, 0.0177555, 0.0348009), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("reflection", bounceData.type);

}
/*
Pixel: [295, 265] Ray: {0 0 14} -> {-0.0509036 0.0529814 -0.997297} T=11.144 Color: (148, 12, 185)
----
Iteration type: Primary
Ray: {0 0 14} -> {-0.0509036 0.0529814 -0.997297}
Ambient: 0.2, 0, 0.2
Diffuse: 0.231378, 0, 0.231378
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.56727,0.590426,2.88609} -> {0.0108705,-0.0113142,-0.999877}
Ambient: 0.2, 0, 0.2
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.504252,0.524835,-2.91038} -> {0.0725581,-0.0755198 ,-0.994501}
Ambient: 0.08, 0.08, 0.32
Diffuse: 0.113921, 0.113921, 0.455683
Specular: 0, 0, 0
*/

TEST(BounceTest, refract2_1)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/refract2.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(295, 480 - 265 - 1), SceneContext::numBounces);
    Color finalColor = data.material->shade(data);

    EXPECT_EQ(3, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(148, 12, 185, true), finalColor);
    EXPECT_TRUE(MathHelper::equalsEpsilon(data.timeCollided, 11.144));

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0, 0, 14)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(-0.0509036, 0.0529814, -0.997297)));
    EXPECT_EQ(Color(0.2f, 0.0f, 0.2f, 0.5f), bounceData.ambient);
    EXPECT_EQ(Color(0.231378, 0, 0.231378), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

    //refraction 1
    bounceData = data.bounceInfo[1];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.56727, 0.590426, 2.88609)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0108705, -0.0113142, -0.999877)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);

    //refraction 2
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.504252, 0.524835, -2.91038)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0725581, -0.0755198, -0.994501)));
    EXPECT_EQ(Color(0.08, 0.08, 0.32), bounceData.ambient);
    EXPECT_EQ(Color(0.113921, 0.113921, 0.455683), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);

}

/*Pixel: [315, 185] Ray: {0, 0, 14} -> {-0.00931474, -0.112812, -0.993573} T=11.3627 Color: (98, 0, 98)
---
Iteration type: Primary
Ray: {0, 0 ,14} -> {-0.00931474, -0.112812, -0.993573}
Ambient: 0.2, 0, 0.2
Diffuse: 0.0838023, 0, 0.0838023
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.105841, -1.28185, 2.71028} -> {0.0028512, 0.0345313, -0.9994}
Ambient: 0.2, 0, 0.2
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.0901408, -1.09171, -2.79287} -> {0.0149547, 0.181118, -0.983348}
No intersection.
*/
TEST(BounceTest, refract2_2)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/refract2.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(315, 480 - 185 - 1), SceneContext::numBounces);
    Color finalColor = data.material->shade(data);

    EXPECT_EQ(3, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(98, 0, 98, true), finalColor);
    EXPECT_TRUE(MathHelper::equalsEpsilon(data.timeCollided, 11.3627));

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0, 0, 14)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction,
                                          Eigen::Vector3f(-0.00931474, -0.112812, -0.993573)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(0.0838023, 0, 0.0838023), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

    //refraction 1
    bounceData = data.bounceInfo[1];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.105841, -1.28185, 2.71028)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0028512, 0.0345313, -0.9994)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);

    //refraction 2
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.0901408, -1.09171, -2.79287)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0149547, 0.181118, -0.983348)));
    EXPECT_EQ(bounceData.timeCollided, -1);
}

/*
Pixel: [315, 320] Ray: {0,0,14} -> {-0.00924547,0.165391,-0.986185} T=11.9035 Color: (174, 62, 176)
----
Iteration type: Primary
Ray: {0,0,14} -> {-0.00924547,0.165391,-0.986185}
Ambient: 0.2, 0, 0.2
Diffuse: 0.24895, 0, 0.24895
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.110053,1.96873,2.26096} -> {0.00540285,-0.0966511,-0.995304}
Ambient: 0.2, 0, 0.2
Diffuse: 0, 0, 0
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {-0.0836739,1.49684,-2.59856} -> {0.0196786,-0.352028,-0.935782}
Ambient: 0.152, 0.276, 0.16
Diffuse: 0.382482, 0.694507, 0.402612
Specular: 0, 0, 0
*/
TEST(BounceTest, refract2_3)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/refract2.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(315, 320 - 265 - 1), SceneContext::numBounces);
    Color finalColor = data.material->shade(data);

    EXPECT_EQ(3, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(174, 62, 176, true), finalColor);
    EXPECT_TRUE(MathHelper::equalsEpsilon(data.timeCollided, 11.9035));

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0, 0, 14)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(-0.00924547, 0.165391, -0.986185)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(0.24895, 0, 0.24895), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

    //refraction 1
    bounceData = data.bounceInfo[1];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.110053, 1.96873, 2.26096)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction,
                                          Eigen::Vector3f(0.00540285, -0.0966511, -0.995304)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);

    //refraction 2
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(-0.0836739, 1.49684, -2.59856)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.0196786, -0.352028, -0.935782)));
    EXPECT_EQ(Color(0.152, 0.276, 0.16), bounceData.ambient);
    EXPECT_EQ(Color(0.382482, 0.694507, 0.402612), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);
}

/*Pixel: [370, 270] Ray: {0,0,14} -> {0.104422,0.0630671,-0.992531} T=11.429 Color: (101, 35, 102)
----
Iteration type: Primary
Ray: {0,0,14} -> {0.104422,0.0630671,-0.992531}
Ambient: 0.2, 0, 0.2
Diffuse: 0.12175, 0, 0.12175
Specular: 0, 0, 0
----
Iteration type: Refraction
Ray: {1.19344,0.720795,2.5633} -> {-0.0351077,-0.0212037,-0.999159}
Ambient: 0.152, 0.276, 016
Diffuse: 0, 0, 0
Specular: 0, 0, 0
.*/
TEST(BounceTest, refract2_4)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;

    auto arg3 = "res/refract2.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    Shape& sphere = scene.getShape(0);
    Shape& plane = scene.getShape(1);
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(370, 480 - 270 - 1), SceneContext::numBounces);
    Color finalColor = data.material->shade(data);

    EXPECT_EQ(2, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(174, 62, 176, true), finalColor);
    EXPECT_TRUE(MathHelper::equalsEpsilon(data.timeCollided, 11.9035));

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(0, 0, 14)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, Eigen::Vector3f(0.104422, 0.0630671, -0.992531)));
    EXPECT_EQ(Color(0.2, 0, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(0.12175, 0, 0.12175), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

    //refraction 1
    bounceData = data.bounceInfo[1];
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, Eigen::Vector3f(1.19344, 0.720795, 2.5633)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction,
                                          Eigen::Vector3f(-0.0351077, -0.0212037, -0.999159)));
    EXPECT_EQ(Color(0.152, 0.276, 016), bounceData.ambient);
    EXPECT_EQ(Color(), bounceData.diffuse);
    EXPECT_EQ(Color(), bounceData.specular);
    EXPECT_EQ("refraction", bounceData.type);
}