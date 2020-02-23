#include <iostream>
#include <typeinfo>
#include <vector>
#include <fstream>
#include "./Matrix/Matrix.hpp"
#include "./Command/ReadWrite/ReadMatrix.hpp"

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

    Matrix* matrix = ReadMatrix::execute(&fin);

    Matrix* m = matrix->getInverseMatrix();

    m->printMatrix();

    return 0;
}
