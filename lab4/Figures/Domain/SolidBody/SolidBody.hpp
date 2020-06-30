#pragma once

#include "../Body/Body.hpp"

class SolidBody: public Body
{
protected:
    double density;
    double volume;
public:
    SolidBody(double density, double volume): density(density), volume(volume) {}
    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
};
