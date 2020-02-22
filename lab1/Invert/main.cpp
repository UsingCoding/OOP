#include <iostream>
#include <typeinfo>
#include "./Matrix/Matrix.hpp"
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> m = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
    Matrix *matrix = new Matrix(&(m));
    std::cout << matrix->calcDeterminant() << std::endl;
    // matrix->getCompanionMatrix();
    matrix->test();
    return 0;
}
