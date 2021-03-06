#pragma once

#include "UnitOfArithmetic.hpp"
#include "../ArithmeticOperations/ArithmeticOperations.hpp"
#include <memory>

class Function: public UnitOfArithmetic
{
private:
    ArithmeticOperaions::ArithmeticOperation operation;
    std::shared_ptr<UnitOfArithmetic> firstOperand;
    std::shared_ptr<UnitOfArithmetic> secondOperand;

public:
    Function(std::shared_ptr<UnitOfArithmetic> firstOperand, std::shared_ptr<UnitOfArithmetic> secondOperand, ArithmeticOperaions::ArithmeticOperation newOperation):
    firstOperand(firstOperand), secondOperand(secondOperand), operation(newOperation) {}

    Function(std::shared_ptr<UnitOfArithmetic> firstOperand):
    firstOperand(firstOperand), operation(nullptr) {}

    operator double() const override;
    operator std::string() const override;
    bool IsDefined() const override;

    double GetRawValue() const override;
};
