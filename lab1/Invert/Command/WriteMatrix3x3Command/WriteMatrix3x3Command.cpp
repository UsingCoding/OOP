#include "./WriteMatrix3x3Command.hpp"

void WriteMatrix3x3Command::Execute(std::ostream &out, const Matrix3x3 * matrix)
{
    out << matrix;
}
