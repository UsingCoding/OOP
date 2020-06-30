#pragma once

#include "../SolidBody/SolidBody.hpp"

class Parallelepiped: public SolidBody
{
private:
    double height;
    double depth;
    double width;
public:
    Parallelepiped(double density, double volume, double height, double depth, double width):
    SolidBody(density, volume), height(height), depth(depth), width(width) {}

    double GetHeight() const;
    double GetWidht() const;
    double GetDepth() const;
    operator std::string() const override;
};
