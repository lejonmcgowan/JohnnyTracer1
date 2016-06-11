//
// Created by lejonmcgowan on 5/18/16.
//

#include <include/gtest/gtest.h>
#include <util/SceneContext.h>
#include <cameras/PinholeCamera.h>
#include <geometry/Shape.h>
#include <fileparsing/POVParser.h>
#include <util/MathUtils.h>

/*Pixel: [399, 280] Ray: {0 0 12} -> {0.162835, 0.0829541, -0.98316} T=10.2326 Color: (129, 13, 129)
----
Iteration type: Primary
Ray: {0 0 12} -> {0.162835 0.0829541 -0.98316}
Hit Object ID (2) at T = 10.2326, Intersection = {1.66623 0.848837 1.93971}
Normal {0.0799673, 0.0959911, 0.969855}
Transformed Ray: {-1.08757 -0.253571 12} -> {0.112521 0.0719996 -0.98316}
Ambient: 0.2, 0.02, 0.2
Diffuse: 0.291907, 0.0291907, 0.291907
Specular: 0.0158587, 0.00158587, 0.0158587

-----------------------------------------------------------------------------------------------------------------------
*/
typedef Eigen::Vector3f vec3;

TEST(TransformTest, transform1)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;
    SceneContext::octreeAcceleration = false;

    auto arg3 = "res/valentine.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(399, 480 - 280 - 1), SceneContext::numBounces);
    EXPECT_EQ(2, data.index + 1);
    EXPECT_TRUE(MathHelper::equalsEpsilon(10.2326, data.timeCollided, 0.0001f));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(-1.08757, -0.253571, 12), data.transformedRay.origin));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(0.112521, 0.0719996, -0.98316), data.transformedRay.direction));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(0.0799673, 0.0959911, 0.969855).normalized(), data.normal));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(1.66623, 0.848837, 1.93971), data.hitPoint));

    Color finalColor = data.material->shade(data);
    EXPECT_EQ(1, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(129, 13, 129, true), finalColor);

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, vec3(0, 0, 12)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, vec3(0.162835, 0.0829541, -0.98316)));
    EXPECT_EQ(Color(0.2, 0.02, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(0.291907, 0.0291907, 0.291907), bounceData.diffuse);
    EXPECT_EQ(Color(0.0158587, 0.00158587, 0.0158587), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

}

/*Pixel: [240, 280] Ray: {0 0 12} -> {-0.162835, 0.0829541, -0.98316} T=10.2326 Color: (211, 21, 211)
----
Iteration type: Primary
Ray: {0 0 12} -> {-0.162835, 0.0829541, -0.98316}
Hit Object ID (1) at T = 10.2326, Intersection = {-1.66623 0.848837 1.93971}
Normal {-0.0799673, 0.0959911, 0.969855}
Transformed Ray: {1.08757, -0.253571, 12} -> {-0.112521, 0.0719996, -0.98316}
Ambient: 0.2, 0.02, 0.2
Diffuse: 0.357024, 0.0357024, 0.357024
Specular: 0.269973, 0.0269973, 0.269973*/

TEST(TransformTest, transform2)
{
    SceneContext::windowDims[0] = 640;
    SceneContext::windowDims[1] = 480;
    SceneContext::aspect = 640 / 480.0f;
    SceneContext::octreeAcceleration = false;

    auto arg3 = "res/valentine.pov";
    Scene scene = POVParser::parseFile(std::string(arg3));
    PinholeCamera *camera = dynamic_cast<PinholeCamera *>(scene.getCamera(0).get());
    auto data = scene.castRay(camera->getProjRay(240, 480 - 280 - 1), SceneContext::numBounces);
    EXPECT_EQ(1, data.index + 1);
    EXPECT_TRUE(MathHelper::equalsEpsilon(10.2326, data.timeCollided, 0.0001f));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(1.08757, -0.253571, 12), data.transformedRay.origin));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(-0.112521, 0.0719996, -0.98316), data.transformedRay.direction));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(-0.0799673, 0.0959911, 0.969855).normalized(), data.normal));
    EXPECT_TRUE(MathHelper::equalsEpsilon(vec3(-1.66623, 0.848837, 1.93971), data.hitPoint));

    Color finalColor = data.material->shade(data);
    EXPECT_EQ(1, data.bounceInfo.size());
    auto bounceData = data.bounceInfo[0];
    EXPECT_EQ(Color(211, 21, 211, true), finalColor);

    //get primary ray information
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.origin, vec3(0, 0, 12)));
    EXPECT_TRUE(MathHelper::equalsEpsilon(bounceData.ray.direction, vec3(-0.162835, 0.0829541, -0.98316)));
    EXPECT_EQ(Color(0.2, 0.02, 0.2), bounceData.ambient);
    EXPECT_EQ(Color(0.357024, 0.0357024, 0.357024), bounceData.diffuse);
    EXPECT_EQ(Color(0.269973, 0.0269973, 0.269973), bounceData.specular);
    EXPECT_EQ("primary", bounceData.type);

}