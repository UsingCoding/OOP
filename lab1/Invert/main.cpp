#include <iostream>
#include <typeinfo>
#include <vector>
#include <fstream>
#include "./Matrix/Matrix.hpp"
#include "./Command/Read/ReadMatrix.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "Not enough arguments" << std::endl;
    }

    std::ifstream fin;
    fin.open(argv[1]);

    if (!fin.is_open())
    {
        std::cout << "Failed to open file" << std::endl;
        return 1;
    }

    Matrix* matrix = ReadMatrix::Execute(&fin);
    fin.close();

    Matrix* m = matrix->GetInverseMatrix();

    if (m == nullptr)
    {
        std::cout << "Can`t find inverse matrix" << std::endl;
        return 0;
    }

    m->PrintMatrix();

    delete matrix;
    delete m;

    return 0;
}
