#pragma once
#include "../../Matrix/Matrix.hpp"
#include "../CommandException.hpp"
#include <fstream>

class ReadMatrixCommand
{
public:
    static Matrix* Execute(std::string fileName);
};
