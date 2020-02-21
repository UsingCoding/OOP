#include <iostream>
#include <typeinfo>
#include "./Matrix/Matrix.hpp"
#include <vector>

int main(int argc, char const *argv[])
{
    Matrix<int> matrix;
    std::cout << matrix.calcDeterminant() << std::endl;
    return 0;
}
