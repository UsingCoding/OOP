// https://github.com/UsingCoding/OOP/issues/7#issue-621202695
#pragma once

#include "../SolidBody/SolidBody.hpp"

class BodyRotation: public SolidBody
{
protected:
    double radius;
public:
    BodyRotation(double density, double volume, double radius): SolidBody(density, volume), radius(radius) {}
    virtual double GetBaseRadius() const;
};
