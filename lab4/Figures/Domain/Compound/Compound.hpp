#pragma once

#include "../Body/Body.hpp"

class Compound: public Body
{
public:
    Compound();

    virtual double GetDensity() = 0;
    virtual double GetVolume() = 0;
    virtual double GetMass() = 0;
    virtual operator std::string() = 0;
};
