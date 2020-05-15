#pragma once

#include "UnitOfArithmetic.hpp"
#include <memory>

class Function: public UnitOfArithmetic
{
private:
    double(*operation)(double, double);
    std::shared_ptr<UnitOfArithmetic> firstOperand;
    std::shared_ptr<UnitOfArithmetic> secondOperand;

public:
    Function(std::shared_ptr<UnitOfArithmetic> firstOperand, std::shared_ptr<UnitOfArithmetic> secondOperand, double(*newOperation)(double, double)):
    firstOperand(firstOperand), secondOperand(secondOperand), operation(newOperation) {}
    ~Function();

    Function(const Function&) = default;
    Function& operator=(const Function&) = default;
    operator double() const override;

    double GetRawValue() const override;
};
