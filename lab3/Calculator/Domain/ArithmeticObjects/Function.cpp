#include "./Function.hpp"
#include "../../../../Utils/StringUtils.hpp"

Function::operator double() const
{
    return operation(firstOperand, secondOperand);
}

Function::operator std::string() const
{
    return IsDefined() ? StringUtils::StringConcatenator() << (double) *this : ArithmeticOperaions::NOT_A_NUMBER;
}

double Function::GetRawValue() const
{
    return operation(firstOperand, secondOperand);
}

bool Function::IsDefined() const
{
    return firstOperand->IsDefined() && secondOperand->IsDefined();
}