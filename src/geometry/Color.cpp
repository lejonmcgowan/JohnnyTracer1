//
// Created by lejonmcgowan on 4/16/16.
//

#include <util/MathUtils.h>
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

Color::Color(float r, float g, float b, float f, float t)
    :
    r(r),
    g(g),
    b(b),
    f(f),
    t(t)
{

}
bool operator==(Color lhs, Color rhs)
{
    bool result = true;
    result &= MathHelper::equalsEpsilon(lhs.r, rhs.r, 1e-2);
    result &= MathHelper::equalsEpsilon(lhs.g, rhs.g, 1e-2);
    result &= MathHelper::equalsEpsilon(lhs.b, rhs.b, 1e-2);

    result &= MathHelper::equalsEpsilon(lhs.f, rhs.f);
    result &= MathHelper::equalsEpsilon(lhs.t, rhs.t);
    return result;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, bool clamp)
    :
    f(0.0f),
    t(0.0f)
{
    if (clamp)
    {
        r = MathHelper::clamp(r, (const unsigned char) 0, (const unsigned char) 255);
        g = MathHelper::clamp(g, (const unsigned char) 0, (const unsigned char) 255);
        b = MathHelper::clamp(b, (const unsigned char) 0, (const unsigned char) 255);
    }

    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
}
Color::Color(Eigen::VectorXf color)
{
    r = color[0];
    g = color[1];
    b = color[2];

    f = color.size() > 3 ? color[3] : 0.0f;
    t = color.size() > 4 ? color[4] : 0.0f;
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    os << "rgb: (" << color.r << "," << color.g << "," << color.b;
    if (color.f > 0)
    {
        os << ",f = " << color.f;
    }
    if (color.t > 0)
    {
        os << ",t = " << color.t;
    }
    os << ")";

    return os;
}








