#pragma once

#include <string>

class Body
{
public:
    Body() {}
    virtual ~Body(){}
    virtual double GetDensity() const = 0;
    virtual double GetVolume() const = 0;
    virtual double GetMass() const = 0;
    virtual operator std::string() const = 0;
};
