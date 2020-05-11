#pragma once

#include "./UnitOfArithmetic.hpp"

class Variable: public UnitOfArithmetic
{
private:
    double value;
public:
    Variable();
    Variable(double newValue);
    ~Variable();

    operator double() const;

    double GetRawValue() const override;
    void SetValue(double newValue);
};
