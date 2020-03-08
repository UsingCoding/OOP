#include "./WriteMatrixCommand.hpp"

void WriteMatrixCommand::Execute(std::ostream &out, Matrix* matrix)
{
    out << *matrix;
}
