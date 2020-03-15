#pragma once
#include "../../Matrix3x3/Matrix3x3.hpp"

class ReadMatrixCommand
{
public:
    static Matrix3x3* Execute(std::string fileName);
};
