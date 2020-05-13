#pragma once

#include "./UnitOfArithmetic.hpp"

class Variable: public UnitOfArithmetic
{
private:
    double value;
    bool isInitilized;
public:
    Variable();
    Variable(double newValue);
    ~Variable();

    operator double() const override;

    double GetRawValue() const override;
    void SetValue(double newValue);
};
