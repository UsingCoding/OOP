#pragma once

#include "../Body/Body.hpp"

class Parallelepiped: public Body
{
private:
    double height;
    double depth;
    double width;
public:
    Parallelepiped(double density, double volume, double height, double depth, double width):
    Body(density, volume), height(height), depth(depth), width(width) {}

    double GetHeight() const;
    double GetWidht() const;
    double GetDepth() const;
    operator std::string() const override;
};
