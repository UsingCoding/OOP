#include "./ReadMatrixCommand.hpp"
#include <iostream>

Matrix* ReadMatrixCommand::Execute(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    if (!fin.is_open())
    {
        throw CommandException("File not found");
    }

    std::vector<std::vector<float>> m;
    float currCoef;

    for (size_t i = 0; i < Matrix::SIZE; i++)
    {
        m.push_back(std::vector<float>{});
        for (size_t j = 0; j < Matrix::SIZE; j++)
        {
            fin >> currCoef;
            m[i].push_back(currCoef);
        }
    }

    fin.close();
    return new Matrix(&m);
}
