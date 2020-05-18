#include "./ArithmeticOperations.hpp"
#include <stdexcept>

double ArithmeticOperaions::Add(double firstArg, double secondArg)
{    
    return firstArg + secondArg;
}

double ArithmeticOperaions::Subtraction(double firstArg, double secondArg)
{
    return firstArg - secondArg;
}

double ArithmeticOperaions::Multiply(double firstArg, double secondArg)
{
    return firstArg * secondArg;
}

double ArithmeticOperaions::Divide(double firstArg, double secondArg)
{
    if (secondArg == 0)
    {
        throw std::domain_error("You can`t divide by zero");
    }
    
    return firstArg / secondArg;
}
