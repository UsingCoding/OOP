#pragma once
#include "../../Matrix/Matrix.hpp"
#include <fstream>

class ReadMatrix
{
public:
    static Matrix* Execute(std::ifstream* fin);
};
