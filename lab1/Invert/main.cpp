#include "./Matrix3x3/Matrix3x3.hpp"
#include "./Command/ReadMatrix3x3Command/ReadMatrix3x3Command.hpp"
#include "./Command/WriteMatrix3x3Command/WriteMatrix3x3Command.hpp"
#include "./Command/CommandException.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect count of arguments" << std::endl;
        return 1;
    }

    Matrix3x3* matrix3x3;

    try
    {
        matrix3x3 = ReadMatrix3x3Command::Execute(argv[1]);
    }
    catch(const CommandException& e)
    {
        std::cerr << e.GetMessage() << std::endl;
        return 1;
    }

    Matrix3x3* inverseMatrix3x3 = matrix3x3->GetInverseMatrix();

    if (inverseMatrix3x3 == nullptr)
    {
        std::cout << "Can`t find inverse matrix" << std::endl;
        delete matrix3x3;
        return 1;
    }

    WriteMatrix3x3Command::Execute(std::cout, inverseMatrix3x3);

    delete matrix3x3;
    delete inverseMatrix3x3;

    return 0;
}
