#include <iostream>
#include <typeinfo>
#include <vector>
#include "./Matrix/Matrix.hpp"
#include "./Command/ReadMatrixCommand/ReadMatrixCommand.hpp"
#include "./Command/WriteMatrixCommand/WriteMatrixCommand.hpp"
#include "./Command/CommandException.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    Matrix* matrix;

    try
    {
        matrix = ReadMatrixCommand::Execute(argv[1]);
    }
    catch(const CommandException& e)
    {
        std::cerr << e.GetMessage() << std::endl;
        return 1;
    }

    Matrix* m = matrix->GetInverseMatrix();

    if (m == nullptr)
    {
        std::cout << "Can`t find inverse matrix" << std::endl;
        return 1;
    }

    WriteMatrixCommand::Execute(std::cout, m);

    delete matrix;
    delete m;

    return 0;
}
