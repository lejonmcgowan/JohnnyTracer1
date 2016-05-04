//#include <include/gtest/gtest.h>
//#include <Eigen/Dense>
//#include "../src/geometry/Ray.h"
//#include "../src/geometry/Sphere.h"
//#include "../src/util/MathUtils.h"
//
//using namespace Eigen;
////globals I'll fix later
//Sphere sphere1(1.01f,Eigen::Vector3f(0,0,0)),
//       sphere2(2.25f,Eigen::Vector3f(0,0,-1.5)),
//       sphere3(3.75f,Eigen::Vector3f(0,0,-4.5)),
//       sphere4(1.1f,Eigen::Vector3f(-5.5,3,0));
//
//Eigen::Vector2f resolution(640,480);
//
//Eigen::Vector3f u(0,1,0),
//                v(1.33333,0,0),
//                w(u.cross(v));
//
////so I (and GoogleTest) can verify the contents of vectors
//std::ostream& operator<<(std::ostream& ostream, const Eigen::Vector3f vec3)
//{
//    return ostream << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")";
//}
//
//std::ostream& operator<<(std::ostream& ostream, const Eigen::Vector2f vec2)
//{
//    return ostream << "(" << vec2[0] << "," << vec2[1] << ")";
//}
//struct RayTraceState
//{
//    Eigen::Vector2f pixel;
//    Ray ray;
//    bool isHit;
//    double timeHit;
//    Eigen::Vector3f color;
//    Eigen::Vector3f hitPosition;
//
//    RayTraceState(Eigen::Vector2f pixel, Ray ray, bool isHit, double timeHit,
//                  Eigen::Vector3f color, Eigen::Vector3f hitPosition = Eigen::Vector3f()) :
//                    pixel(pixel),
//                    isHit(isHit),
//                    timeHit(timeHit),
//                    color(color),
//                    hitPosition(hitPosition)
//    {
//        this->ray.direction = ray.direction;
//        this->ray.origin = ray.origin;
//    }
//
//    RayTraceState() = default;
//    RayTraceState(const RayTraceState& state)
//    {
//        pixel = state.pixel;
//        ray.origin = state.ray.origin;
//        ray.direction = state.ray.direction;
//        hitPosition = state.hitPosition;
//        isHit = state.isHit;
//        timeHit = state.timeHit;
//        color = state.color;
//    }
//
//    friend std::ostream& operator<<(std::ostream& ostream, const RayTraceState traceState)
//    {
//        std::string hit =  traceState.isHit ? "(" + std::to_string(traceState.hitPosition[0]) + ","
//                                              + std::to_string(traceState.hitPosition[1]) + ","
//                                              + std::to_string(traceState.hitPosition[2]) + ")"
//                                            : "no hit";
//
//        std::string color =  traceState.isHit ? "(" + std::to_string(traceState.color[0]) + ","
//                                                + std::to_string(traceState.color[1]) + ","
//                                                + std::to_string(traceState.color[2]) + ")"
//                                              : "no hit";
//
//        std::string hitTime = traceState.isHit ? std::to_string(traceState.timeHit) : "no hit";
//
//        return ostream << "Pixel: " << traceState.pixel
//               << "Ray (origin, direction): " << traceState.ray.origin << " " << traceState.ray.direction << std::endl
//               << "hit point: " << hit << std::endl
//               << "time hit: " << hitTime << std::endl
//               << color << std::endl;
//    }
//};
//
//struct RayTraceTest: public testing::Test
//{
//private:
//    void setColors()
//    {
//        sphere1.setColor(Eigen::Vector3f(255,255,255));
//        sphere2.setColor(Eigen::Vector3f(0,0,0));
//        sphere3.setColor(Eigen::Vector3f(64,64,64));
//        sphere4.setColor(Eigen::Vector3f(31,87,143));
//    }
//public:
//    std::vector<Shape *> objects;
//    RayTraceState* traceState;
//
//    RayTraceTest()
//    {
//        traceState = new RayTraceState();
//        setColors();
//        objects.push_back(&sphere1);
//        objects.push_back(&sphere2);
//        objects.push_back(&sphere3);
//        objects.push_back(&sphere4);
//    }
//    ~RayTraceTest()
//    {
//        objects.clear();
//    }
//};
//
//struct RayTraceUnitTest1: public RayTraceTest
//{
//    RayTraceState traceState;
//
//    void setState(RayTraceState traceState)
//    {
//        this->traceState = traceState;
//    }
//
//    HitData raytrace()
//    {
//        HitData shadeData;
//        double tmin = -1;
//        bool firstTime;
//        Eigen::Vector3f vp = w + w.normalized();
//        Ray myRay;
//        myRay.origin = traceState.ray.origin;
//        float su,sv;
//
//        su = traceState.pixel[0]  / resolution[0] + 0.5f;
//        sv = traceState.pixel[1] / resolution[1] + 0.5f;
//        su *= resolution[0] / resolution[1];
//
//        myRay.direction = -w + su * u + sv * v;
//        EXPECT_EQ(myRay.direction.normalized(),traceState.ray.direction);
//        for(auto shape: objects)
//        {
//            if(shape->hit(myRay,shadeData) && (shadeData.timeCollided < tmin || firstTime))
//            {
//                tmin = shadeData.timeCollided;
//                shadeData.color = shape->getColor();
//                firstTime = false;
//            }
//        }
//        return shadeData;
//    }
//};
//
//
//TEST_F(RayTraceUnitTest1, Testsuite)
//{
//    RayTraceState test1,test2,test3,test4,test5;
//
//    std::cout << w << std::endl;
//
//    test1.pixel = Eigen::Vector2f(320,239);
//    test1.ray.origin = Eigen::Vector3f(0,0,14);
//    test1.ray.direction = Eigen::Vector3f(0.00104165, -0.00104168, -0.999999);
//    test1.timeHit = 12.9902f;
//    test1.color = Eigen::Vector3f(255,255,255);
//
//    test2.pixel = Eigen::Vector2f(360,219);
//    test2.ray.origin = Eigen::Vector3f(0,0,14);
//    test1.ray.direction = Eigen::Vector3f(0.084,-0.0425186,-0.995558);
//    test2.timeHit = 13.71856f;
//    test2.color = Eigen::Vector3f(255,255,255);
//
//    test3.pixel = Eigen::Vector2f(230,239);
//    test3.ray.origin = Eigen::Vector3f(0,0,14);
//    test1.ray.direction = Eigen::Vector3f(-0.183299,-0.00102403, -0.983057);
//    test3.timeHit = 16.58557f;
//    test3.color = Eigen::Vector3f(255,255,255);
//
//    test4.pixel = Eigen::Vector2f(120,349);
//    test4.ray.origin = Eigen::Vector3f(0,0,14);
//    test1.ray.direction = Eigen::Vector3f(-0.375553,0.206131,-0.903587);
//    test4.timeHit = 14.28708f;
//    test4.color = Eigen::Vector3f(255,255,255);
//
//    test5.pixel = Eigen::Vector2f(490,119);
//    test5.ray.origin = Eigen::Vector3f(0,0,14);
//    test1.ray.direction = Eigen::Vector3f(-0.325728,0.230207,-0.917009);
//    test5.timeHit = -1;
//    test5.color = Eigen::Vector3f(255,255,255);
//
//    std::vector<RayTraceState> tests;
//    tests.push_back(test1);
//    tests.push_back(test2);
//    tests.push_back(test3);
//    tests.push_back(test4);
//    tests.push_back(test5);
//
//    for(auto test: tests)
//    {
//        setState(test);
//        auto finalHitData = raytrace();
//        EXPECT_EQ(test.isHit, finalHitData.hit);
//        if (test.isHit)
//        {
//            //EXPECT_EQ(test.hitPosition, finalHitData.hitPoint);
//            EXPECT_EQ(test.color, finalHitData.color);
//            EXPECT_EQ(test.timeHit, finalHitData.timeCollided);
//        }
//    }
//
//
//}
//
//TEST_F(RayTraceUnitTest1, MyTestsuite)
//{
//    Vector2f mappedCoords = MathHelper::mapCoords(Vector2f(320.5,239.5),
//                          Vector4f(0,resolution[0],0,resolution[1]),
//                          Vector4f(-1.3333 / 2,1.3333 / 2,-0.5,0.5));
//
//    Vector3f finalResult = -1 * (-w + mappedCoords[0] * u + mappedCoords[1] * v);
//    finalResult.normalize();
//    EXPECT_EQ(Vector3f(0.00104165,-0.00104168,-0.999999),finalResult);
//}
//
///*
// * (320, 239)  {0 0 14} -> {0.00104165 -0.00104168 -0.999,999}  12.9902     (255, 255, 255)
//   (360, 219)  {0 0 14} -> {0.084 -0.0425186 -0.995558}        13.71856    (0, 0, 0)
//   (230, 239)  {0 0 14} -> {-0.183299 -0.00102403 -0.983057}   16.58557    (64, 64, 64)
//   (120, 349)  {0 0 14} -> {-0.375553 0.206131 -0.903587}      14.28708    (31, 87, 143)
//   (490, 119)  {0 0 14} -> {0.325728 -0.230207 -0.917009}      no hit      no hit
//
//       sphere1(1.01f,Eigen::Vector3f(0,0,0)),
//       sphere2(2.25f,Eigen::Vector3f(0,0,-1.5)),
//       sphere3(3.75f,Eigen::Vector3f(0,0,-4.5)),
//       sphere4(1.1f,Eigen::Vector3f(-5.5,3,0));
//
//        sphere1.setColor(Eigen::Vector3f(255,255,255));
//        sphere2.setColor(Eigen::Vector3f(0,0,0));
//        sphere3.setColor(Eigen::Vector3f(64,64,64));
//        sphere4.setColor(Eigen::Vector3f(31,87,143));
//   */
//
///*
//void setColors()
//{
//    sphere1.setColor(Eigen::Vector3f(255,255,255));
//    sphere2.setColor(Eigen::Vector3f(0,0,0));
//    sphere3.setColor(Eigen::Vector3f(64,64,64));
//    sphere4.setColor(Eigen::Vector3f(31,87,143));
//}
//
//TEST(BaseTest,Sanity)
//{
//    EXPECT_EQ(2,2);
//    EXPECT_EQ(false, 3 == 2);
//}
//
//HitData testCast(Eigen::Vector2f pixel)
//{
//    HitData shadeData;
//    double tmin;
//    bool firstTime;
//
//    Eigen::Vector3f origin(0,0,14);
//    Eigen::Vector3f direction(0,0,-1);
//    Ray ray(origin,direction);
//    float x = 0, y = 0;
//    x = pixel[0] - 0.5f * resolution[0];
//    y = pixel[1] - 0.5f * resolution[1];
//    ray.origin << x,y,ray.origin[2];
//
//    std::vector<Shape *> shapes;
//    shapes.push_back(&sphere1);
//    shapes.push_back(&sphere2);
//    shapes.push_back(&sphere3);
//    shapes.push_back(&sphere4);
//
//    for(auto shape: shapes)
//    {
//        if(shape->hit(ray,shadeData) && (shadeData.timeCollided < tmin || firstTime))
//        {
//            tmin = shadeData.timeCollided;
//            shadeData.color = shape->getColor();
//            firstTime = false;
//
//        }
//    }
//
//    return shadeData;
//}
//TEST(BaseTest, RayTest1)
//{
//    setColors();
//    HitData hitData = testCast(Eigen::Vector2f(320,239));
//
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.hitPoint);
//    EXPECT_EQ(0.0f,hitData.timeCollided);
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.color);
//
//}
//
//TEST(BaseTest, RayTest2)
//{
//    setColors();
//    HitData hitData = testCast(Eigen::Vector2f(360,219));
//
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.hitPoint);
//    EXPECT_EQ(0.0f,hitData.timeCollided);
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.color);
//}
//
//TEST(BaseTest, RayTest3)
//{
//    setColors();
//    HitData hitData = testCast(Eigen::Vector2f(230,239));
//
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.hitPoint);
//    EXPECT_EQ(0.0f,hitData.timeCollided);
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.color);
//}
//
//TEST(BaseTest, RayTest4)
//{
//    setColors();
//    HitData hitData = testCast(Eigen::Vector2f(120,349));
//
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.hitPoint);
//    EXPECT_EQ(0.0f,hitData.timeCollided);
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.color);
//}
//
//TEST(BaseTest, RayTest5)
//{
//    setColors();
//    HitData hitData = testCast(Eigen::Vector2f(490,119));
//
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.hitPoint);
//    EXPECT_EQ(0.0f,hitData.timeCollided);
//    EXPECT_EQ(Eigen::Vector3f(0,0,0),hitData.color);
//}
// */