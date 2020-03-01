#include "ReadMap.hpp"
#include <iostream>

void ReadMap::execute(std::ifstream* fin, char (*map)[Config::SIZE])
{
    std::string line;
    int count = 0;
    while (!(*fin).eof())
    {
        getline((*fin), line);
        if (line.size() != 0)
        {
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] != ' ')
                {
                    map[count][i] = line[i];
                }
            }
        }
        // if (count == 4)
        // {
        //     break;
        // }
        ++count;
    }


    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < 100; j++)
        {
            std::cout << map[i][j];
        }

        std::cout << std::endl;
    }

}
