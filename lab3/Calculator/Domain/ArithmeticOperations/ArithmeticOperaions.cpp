#include "./ArithmeticOperations.hpp"
#include <stdexcept>
#include "../../../../Utils/StringUtils.hpp"

std::string ArithmeticOperaions::NOT_A_NUMBER = "NaN";

double ArithmeticOperaions::Add(std::shared_ptr<UnitOfArithmetic> & firstArg, std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }
    
    return *(firstArg) + *(secondArg);
}

double ArithmeticOperaions::Subtraction(std::shared_ptr<UnitOfArithmetic> & firstArg, std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }

    return *(firstArg) - *(secondArg);
}

double ArithmeticOperaions::Multiply(std::shared_ptr<UnitOfArithmetic> & firstArg, std::shared_ptr<UnitOfArithmetic> & secondArg)
{
    if (!firstArg->IsDefined() || !secondArg->IsDefined())
    {
        throw std::logic_error(ArithmeticOperaions::NOT_A_NUMBER);
    }

    return *(firstArg) * *(secondArg);
}

double ArithmeticOperaions::Divide(std::shared_ptr<UnitOfArithmetic> & firstArg, std::shared_ptr<UnitOfArithmetic> & secondArg)
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
