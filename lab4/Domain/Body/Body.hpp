#pragma once

#include <string>

class Body
{
public:
    virtual ~Body(){}
    virtual double GetDensity() = 0;
    virtual double GetVolume() = 0;
    virtual double GetMass() = 0;
    virtual operator std::string() = 0;
};
