#pragma once

class UnitOfArithmetic
{
public:
    virtual double GetRawValue() const = 0;
    virtual ~UnitOfArithmetic() {};
    virtual operator double() const = 0;
    virtual bool IsDefined() const = 0;
};
