#pragma once
#include "../../Matrix3x3/Matrix3x3.hpp"
#include "../CommandException.hpp"
#include <fstream>

class ReadMatrixCommand
{
public:
    static Matrix3x3* Execute(std::string fileName);
};
