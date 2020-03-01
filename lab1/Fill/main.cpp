#include <iostream>
#include <fstream>
#include "Config/Config.hpp"
#include "Command/ReadMap.hpp"

int main(int argc, char const *argv[])
{
    if (argc <= 2)
    {
        std::cout << "Missing args" << std::endl;
        return 0;
    }

    char map[Config::SIZE][Config::SIZE];

    std::ifstream fin;
    fin.open(argv[1]);

    if (!fin.is_open())
    {
        std::cout << "Failed to open file" << std::endl;
        return 0;
    }

    ReadMap::execute(&fin, map);


    return 0;
}
