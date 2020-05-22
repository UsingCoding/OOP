// https://github.com/UsingCoding/OOP/issues/7#issue-621202695
#pragma once

#include "../Body/Body.hpp"

class BodyRotation: public Body
{
public:
    virtual double GetBaseRadius() = 0;
};
