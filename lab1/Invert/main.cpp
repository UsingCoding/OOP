#include <iostream>
#include <typeinfo>
#include <vector>
#include "./Matrix3x3/Matrix3x3.hpp"
#include "./Command/ReadMatrix3x3Command/ReadMatrix3x3Command.hpp"
#include "./Command/WriteMatrix3x3Command/WriteMatrix3x3Command.hpp"
#include "./Command/CommandException.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    Matrix3x3* matrix;

    try
    {
        matrix = ReadMatrixCommand::Execute(argv[1]);
    }
    catch(const CommandException& e)
    {
        std::cerr << e.GetMessage() << std::endl;
        return 1;
    }

    Matrix3x3* inverseMatrix = matrix->GetInverseMatrix();

    if (inverseMatrix == nullptr)
    {
        std::cout << "Can`t find inverse matrix" << std::endl;
        return 1;
    }

    WriteMatrixCommand::Execute(std::cout, inverseMatrix);

    delete matrix;
    delete inverseMatrix;

    return 0;
}
