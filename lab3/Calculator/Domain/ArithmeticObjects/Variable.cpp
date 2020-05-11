#include "./Variable.hpp"

Variable::Variable()
{

}

Variable::Variable(double newValue)
{
    value = newValue;
}

Variable::~Variable()
{

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