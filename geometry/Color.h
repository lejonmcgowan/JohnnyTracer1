//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_COLOR_H
#define RAYTRACER473_COLOR_H

#include <Eigen/Dense>
#include <vector>

class Color
{
public:
    float r, g, b, f, t;

    Color();
    Color(float r, float g, float b, float f = 0.0f, float t = 0.0f);
    Color(unsigned char r, unsigned char g, unsigned char b, bool clamp);
    Color(const Color& otherColor);
    Color(Eigen::VectorXf color);

    void setRGB(float r, float g, float b);
    void setRGB(Eigen::Vector3f rgb);
    void setRGBF(float r, float g, float b, float f);
    void setRGBF(Eigen::Vector4f rgbf);
    void setRGBT(float r, float g, float b, float t);
    void setRGBFT(float r, float g, float b, float f, float t);


    Eigen::Vector3f getRGB();
    Eigen::Vector4f getRGBF();
    Eigen::Vector4f getRGBT();
    Eigen::VectorXf getRGBFT();

    Color& operator=(Color otherColor);
    void addColor(Eigen::Vector3f otherColor);
    static Color averageColors(std::vector<Color>& colors);
    void clamp();
};

bool operator==(const Color lhs, const Color rhs);
std::ostream& operator<<(std::ostream& os, const Color& obj);
#endif //RAYTRACER473_COLOR_H
