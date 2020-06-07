// https://github.com/UsingCoding/OOP/issues/7#issue-621202695
#pragma once

#include "../Body/Body.hpp"

class BodyRotation: public Body
{
protected:
    double radius;
public:
    BodyRotation(double density, double volume, double radius): Body(density, volume), radius(radius) {}
    virtual double GetBaseRadius() const;
};
