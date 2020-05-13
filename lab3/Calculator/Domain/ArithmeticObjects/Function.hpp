#pragma once

#include "UnitOfArithmetic.hpp"
#include <memory>

class Function: public UnitOfArithmetic
{
private:
    double(*operation)(double, double);
    std::unique_ptr<UnitOfArithmetic> & firstOperand;
    std::unique_ptr<UnitOfArithmetic> & secondOperand;

public:
    Function(std::unique_ptr<UnitOfArithmetic> & firstOperand, std::unique_ptr<UnitOfArithmetic> & secondOperand);
    ~Function();

    Function(const Function&) = default;
    Function& operator=(const Function&) = default;
    void SetOperation(double(*newOperation)(double, double));
    operator double() const override;

    double GetRawValue() const override;
};
