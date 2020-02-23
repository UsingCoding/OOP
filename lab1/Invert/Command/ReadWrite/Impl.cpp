#include "./ReadMatrix.hpp"

#include <iostream>

Matrix* ReadMatrix::execute(std::ifstream* fin)
{
    std::vector<std::vector<float>> m;
    float currCoef;

    for (size_t i = 0; i < Matrix::SIZE; i++)
    {
        m.push_back(std::vector<float>{});
        for (size_t j = 0; j < Matrix::SIZE; j++)
        {
            (*fin) >> currCoef;
            m[i].push_back(currCoef);
        }
    }

    return new Matrix(&m);
}
