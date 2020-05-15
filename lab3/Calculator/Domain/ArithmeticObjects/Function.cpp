#include "./Function.hpp"

Function::~Function()
{

}

Function::operator double() const
{
    return operation(*firstOperand, *secondOperand);
}

double Function::GetRawValue() const
{
    return operation(*firstOperand, *secondOperand);
}