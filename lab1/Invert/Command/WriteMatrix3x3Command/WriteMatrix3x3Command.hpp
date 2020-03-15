#pragma once
#include <iostream>
#include "../../Matrix3x3/Matrix3x3.hpp"

class WriteMatrixCommand
{
public:
    static void Execute(std::ostream &out, const Matrix3x3 * matrix);
};
