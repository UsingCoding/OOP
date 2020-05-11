#pragma once

#include "UnitOfArithmetic.hpp"
#include <memory>

class Function: public UnitOfArithmetic
{
private:
    double predicat(UnitOfArithmetic &, UnitOfArithmetic &);
    UnitOfArithmetic & firstOperand;
    UnitOfArithmetic & secondOperand;
public:
    Function();
    ~Function();

    Function(const Function&) = default;
    Function& operator=(const Function&) = default;

    double GetRawValue() const override;
};
