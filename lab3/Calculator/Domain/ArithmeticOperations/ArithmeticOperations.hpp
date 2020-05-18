#pragma once
#include "../ArithmeticObjects/UnitOfArithmetic.hpp"
#include <memory>

namespace ArithmeticOperaions
{
    typedef double (*ArithmeticOperation)(double, double);
    double Add(double, double);
    double Subtraction(double, double);
    double Multiply(double, double);
    double Divide(double, double);
} // namespace ArithmeticOperaions
