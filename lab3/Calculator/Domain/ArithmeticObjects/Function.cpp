#include "./Function.hpp"

Function::operator double() const
{
    return operation(firstOperand, secondOperand);
}

double Function::GetRawValue() const
{
    return operation(firstOperand, secondOperand);
}

bool Function::IsDefined() const
{
    return firstOperand->IsDefined() && secondOperand->IsDefined();
}