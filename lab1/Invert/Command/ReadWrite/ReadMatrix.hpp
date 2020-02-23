#pragma once
#include "../../Matrix/Matrix.hpp"
#include <fstream>

class ReadMatrix
{
public:
    static Matrix* execute(std::ifstream* fin);
};
