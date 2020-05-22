#include "./Variable.hpp"
#include "../../../../Utils/StringUtils.hpp"
#include "../ArithmeticOperations/ArithmeticOperations.hpp"

#include <iostream>

Variable::operator double() const
{
    return value;
}

Variable::operator std::string() const
{
    return isDefined ? (StringUtils::StringConcatenator() << value) : UnitOfArithmetic::NOT_A_NUMBER;
}

double Variable::GetRawValue() const
{
    return value;
}

void Variable::SetValue(double newValue)
{
    value = newValue;
    isDefined = true;
}

bool Variable::IsDefined() const
{
    return isDefined;
}
