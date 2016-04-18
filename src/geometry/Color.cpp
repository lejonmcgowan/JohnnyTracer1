//
// Created by lejonmcgowan on 4/16/16.
//

#include "Color.h"


Eigen::Vector3f Color::getRGB()
{
    Eigen::Vector3f v(r,g,b);
    return v;
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
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setRGBF(float r, float g, float b, float f)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->f = f;
}

void Color::setRGBT(float r, float g, float b, float t)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->t = t;
}

void Color::setRGBFT(float r, float g, float b, float f, float t)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->f = f;
    this->t = t;
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
void Color::setRGB(Eigen::Vector3f rgb)
{
    setRGB(rgb[0],rgb[1],rgb[2]);
}
void Color::addColor(Eigen::Vector3f otherColor)
{
    r += otherColor[0];
    g += otherColor[1];
    b += otherColor[2];
}





