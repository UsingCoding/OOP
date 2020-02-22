#include <iostream>
#include <typeinfo>
#include "./Matrix/Matrix.hpp"
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> m = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
    Matrix *matrix = new Matrix(&(m));
    // Matrix *matrix = new Matrix(&(int {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}}));
    std::cout << matrix->calcDeterminant() << std::endl;
    matrix->getCompanionMatrix();
    return 0;
}
