//
// Created by lejonmcgowan on 4/16/16.
//

#include "Color.h"


Eigen::Vector3f Color::getRGB() {
    return Eigen::Vector3f(r,g,b);
}

Eigen::Vector4f Color::getRGBF()
{
    return Eigen::Vector4f(r,g,b,f);
}

Eigen::VectorXf Color::getRGBFT()
{
    Eigen::VectorXf vec(5);
    vec << r,g,b,f,t;
    return vec;
}

Eigen::Vector4f Color::getRGBT() {
    return Eigen::Vector4f(r,g,b,t);
}

void Color::setRGB(float r, float g, float b)
{

}

void Color::setRGBF(float r, float g, float b, float f)
{

}

void Color::setRGBT(float r, float g, float b, float t)
{

}

void Color::setRGBFT(float r, float g, float b, float f, float t)
{

}
Color& Color::operator=(Color otherColor)
{
    r = otherColor.r;
    g = otherColor.g;
    b = otherColor.b;
    f = otherColor.f;
    t = otherColor.t;

    return *this;
}

Color::Color(const Color& otherColor)
{
    r = otherColor.r;
    g = otherColor.g;
    b = otherColor.b;
    f = otherColor.f;
    t = otherColor.t;
}
Color::Color()
    : r(0), g(0), b(0), f(0), t(0)
{

}

