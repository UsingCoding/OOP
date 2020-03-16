#include "./Matrix3x3/Matrix3x3.hpp"
#include "./ReadException/ReadException.hpp"
#include <fstream>
#include <iostream>
#include <array>
#include <memory>

std::unique_ptr<Matrix3x3> ReadMatrix3x3(std::string fileName);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect count of arguments" << std::endl;
        return 1;
    }

    std::unique_ptr<Matrix3x3> matrix3x3;

    try
    {
        matrix3x3 = ReadMatrix3x3(argv[1]);
    }
    catch(const ReadException& e)
    {
        std::cerr << e.GetMessage() << std::endl;
        return 1;
    }

    std::unique_ptr<Matrix3x3> inverseMatrix3x3 = matrix3x3->GetInverseMatrix();

    if (inverseMatrix3x3 == nullptr)
    {
        std::cout << "Can`t find inverse matrix" << std::endl;
        return 1;
    }

    std::cout << *inverseMatrix3x3;

    return 0;
}

std::unique_ptr<Matrix3x3> ReadMatrix3x3(std::string fileName)
{
    std::ifstream fin;
    fin.open(fileName);

    if (!fin.is_open())
    {
        throw ReadException("Problem with input file");
    }

    std::array<std::array<float, Matrix3x3::SIZE>, Matrix3x3::SIZE>  matrix;
    float currCoef;

    for (size_t i = 0; i < Matrix3x3::SIZE; i++)
    {
        for (size_t j = 0; j < Matrix3x3::SIZE; j++)
        {
            fin >> currCoef;

            if (fin.eof())
            {
                throw ReadException("Not enough matrix coefficients");
            }

            matrix[i][j] = currCoef;
        }
    }

    fin.close();
    return std::move(std::make_unique<Matrix3x3>(matrix));
}
