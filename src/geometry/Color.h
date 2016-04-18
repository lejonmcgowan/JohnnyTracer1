//
// Created by lejonmcgowan on 4/16/16.
//

#ifndef RAYTRACER473_COLOR_H
#define RAYTRACER473_COLOR_H

#include <Eigen/Dense>

class Color
{
public:
    float r, g, b, f, t;

    Color();
    Color(const Color& otherColor);

    void setRGB(float r, float g, float b);
    void setRGB(Eigen::Vector3f rgb);
    void setRGBF(float r, float g, float b, float f);
    void setRGBT(float r, float g, float b, float t);
    void setRGBFT(float r, float g, float b, float f, float t);


    Eigen::Vector3f getRGB();
    Eigen::Vector4f getRGBF();
    Eigen::Vector4f getRGBT();
    Eigen::VectorXf getRGBFT();

    Color& operator=(Color otherColor);
    void addColor(Eigen::Vector3f otherColor);
};


#endif //RAYTRACER473_COLOR_H
