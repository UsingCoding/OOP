#pragma once

class UnitOfArithmetic
{
public:
    virtual double GetRawValue() const = 0;
    virtual ~UnitOfArithmetic() {};
};
