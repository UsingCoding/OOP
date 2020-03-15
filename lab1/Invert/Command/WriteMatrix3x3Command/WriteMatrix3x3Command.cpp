#include "./WriteMatrix3x3Command.hpp"

void WriteMatrixCommand::Execute(std::ostream &out, const Matrix3x3 * matrix)
{
    out << matrix;
}
