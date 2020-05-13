#include "./Variable.hpp"

#include <iostream>

Variable::Variable()
{

}

Variable::Variable(double newValue)
{
    value = newValue;
}

Variable::~Variable()
{
    std::cout << "got me destroyed" << std::endl;
}

Variable::operator double() const
{
    return value;
}

double Variable::GetRawValue() const
{
    return value;
}

void Variable::SetValue(double newValue)
{
    value = newValue;
}