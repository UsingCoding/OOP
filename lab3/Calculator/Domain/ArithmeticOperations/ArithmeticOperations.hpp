#pragma once
#include "../ArithmeticObjects/UnitOfArithmetic.hpp"
#include <memory>

namespace ArithmeticOperaions
{
    typedef double (*ArithmeticOperation)(const std::shared_ptr<UnitOfArithmetic> &, const std::shared_ptr<UnitOfArithmetic> &);
    extern std::string NOT_A_NUMBER;
    double Add(const std::shared_ptr<UnitOfArithmetic> &, const std::shared_ptr<UnitOfArithmetic> &);
    double Subtraction(const std::shared_ptr<UnitOfArithmetic> &, const std::shared_ptr<UnitOfArithmetic> &);
    double Multiply(const std::shared_ptr<UnitOfArithmetic> &, const std::shared_ptr<UnitOfArithmetic> &);
    double Divide(const std::shared_ptr<UnitOfArithmetic> &, const std::shared_ptr<UnitOfArithmetic> &);
} // namespace ArithmeticOperaions
