#pragma once

#include "../BodyRotation/BodyRotation.hpp"

class Cylinder: public BodyRotation
{
private:
    double height;
public:
    Cylinder();

    Cylinder(double density, double volume, double radius, double height): BodyRotation(density, volume, radius), height(height) {}

    double GetHeight() const;
    operator std::string() const override;
};
