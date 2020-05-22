#include "./Function.hpp"
#include "../../../../Utils/StringUtils.hpp"
#include <iostream>

Function::operator double() const
{
    return operation == nullptr ? *(firstOperand) : operation(*(firstOperand), *(secondOperand));
}

Function::operator std::string() const
{
    return IsDefined() ? StringUtils::StringConcatenator() << (double) *this : UnitOfArithmetic::NOT_A_NUMBER;
}

double Function::GetRawValue() const
{
    return operation(*(firstOperand), *(secondOperand));
}

bool Function::IsDefined() const
{
    return firstOperand->IsDefined() && operation == nullptr ?: secondOperand->IsDefined();
}
