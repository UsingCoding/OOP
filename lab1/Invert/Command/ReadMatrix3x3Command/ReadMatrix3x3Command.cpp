#include "./ReadMatrix3x3Command.hpp"
#include <iostream>
#include "../CommandException.hpp"
#include <fstream>

Matrix3x3* ReadMatrixCommand::Execute(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    if (!fin.is_open())
    {
        throw CommandException("Problem with input file");
    }

    std::vector<std::vector<float>> m;
    float currCoef;

    for (size_t i = 0; i < Matrix3x3::SIZE; i++)
    {
        m.push_back(std::vector<float>{});
        for (size_t j = 0; j < Matrix3x3::SIZE; j++)
        {
            fin >> currCoef;

            if (fin.eof())
            {
                throw CommandException("Not enough matrix coefficients");
            }

            // std::cout << currCoef << " " << std::endl;
            m[i].push_back(currCoef);
        }
    }

    fin.close();
    return new Matrix3x3(m);
}
