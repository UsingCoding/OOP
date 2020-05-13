#include "./Function.hpp"

Function::Function(std::unique_ptr<UnitOfArithmetic> & firstOperand, std::unique_ptr<UnitOfArithmetic> & secondOperand): firstOperand(firstOperand), secondOperand(secondOperand)
{

}

Function::~Function()
{

}

void Function::SetOperation(double(*newOperation)(double, double))
{
    operation = newOperation;
}

Function::operator double() const
{
    return operation(*firstOperand, *secondOperand);
}

double Function::GetRawValue() const
{
    return operation(*firstOperand, *secondOperand);
}