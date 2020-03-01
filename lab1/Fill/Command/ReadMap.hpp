#pragma once
#include "../Config/Config.hpp"
#include <fstream>

class ReadMap
{
public:
    static void execute(std::ifstream* fin, char (*map)[Config::SIZE]);
};
