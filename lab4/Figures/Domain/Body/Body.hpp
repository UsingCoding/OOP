#pragma once

#include <string>

class Body
{
protected:
    double density;
    double volume;
public:
    Body(double density, double volume): density(density), volume(volume) {}
    virtual ~Body(){}
    double GetDensity() const;
    double GetVolume() const;
    double GetMass() const;
    virtual operator std::string() const = 0;
};
