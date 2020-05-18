#pragma once

#include <string>

class UnitOfArithmetic
{
public:
    static const std::string NOT_A_NUMBER;

    virtual double GetRawValue() const = 0;
    virtual ~UnitOfArithmetic() {};
    virtual operator double() const = 0;
    virtual operator std::string() const = 0;
    virtual bool IsDefined() const = 0;
};
