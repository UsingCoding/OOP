#include "./Function.hpp"

Function::Function(std::shared_ptr<UnitOfArithmetic> firstOperand, std::shared_ptr<UnitOfArithmetic> secondOperand): firstOperand(firstOperand), secondOperand(secondOperand)
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