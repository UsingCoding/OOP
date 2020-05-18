#include "./ArithmeticOperations.hpp"
#include <stdexcept>

std::string ArithmeticOperaions::NOT_A_NUMBER = "NaN";

double ArithmeticOperaions::Add(const std::shared_ptr<UnitOfArithmetic> & firstArg, const std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }
    
    return *(firstArg) + *(secondArg);
}

double ArithmeticOperaions::Subtraction(const std::shared_ptr<UnitOfArithmetic> & firstArg, const std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }

    return *(firstArg) - *(secondArg);
}

double ArithmeticOperaions::Multiply(const std::shared_ptr<UnitOfArithmetic> & firstArg, const std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }

    return *(firstArg) * *(secondArg);
}

double ArithmeticOperaions::Divide(const std::shared_ptr<UnitOfArithmetic> & firstArg, const std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }

    if (secondArg == 0)
    {
        throw std::domain_error("You can`t divide by zero");
    }
    
    return *(firstArg) / *(secondArg);
}
