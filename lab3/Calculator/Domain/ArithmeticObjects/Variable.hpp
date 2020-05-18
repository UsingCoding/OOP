#pragma once

#include "./UnitOfArithmetic.hpp"

class Variable: public UnitOfArithmetic
{
private:
    double value;
    bool isDefined;
public:
    Variable();
    ~Variable();

    operator double() const override;
    operator std::string() const override;
    double GetRawValue() const override;
    bool IsDefined() const override;

    void SetValue(double newValue);
};
