#pragma once
#include <iostream>
#include "../../Matrix/Matrix.hpp"

class WriteMatrixCommand
{
public:
    static void Execute(std::ostream &out, Matrix* matrix);
};
