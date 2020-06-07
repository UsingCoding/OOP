#pragma once

#include "../BodyRotation/BodyRotation.hpp"

#include <string>

class Cone: public BodyRotation
{
private:
    double height;
public:
    Cone(double density, double volume, double radius, double height): BodyRotation(density, volume, radius), height(height) {}

    double GetHeight() const;
    operator std::string() const override;
};
