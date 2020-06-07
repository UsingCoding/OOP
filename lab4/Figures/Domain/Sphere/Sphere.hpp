#pragma once

#include "../BodyRotation/BodyRotation.hpp"

class Sphere: public BodyRotation
{
public:
    Sphere(double density, double volume, double radius): BodyRotation(density, volume, radius) {}

    operator std::string() const override;
};
