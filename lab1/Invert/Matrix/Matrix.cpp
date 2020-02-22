#include "./Matrix.hpp"
#include <iostream>
#include <cmath>

Matrix::Matrix(std::vector<std::vector<int>>* m)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            coefs[i][j] = (*m)[i][j];
        }
    }

}

int Matrix::calcDeterminant()
{
    return (
        coefs[0][0] * coefs[1][1] * coefs[2][2] +
        coefs[2][0] * coefs[0][1] * coefs[1][2] +
        coefs[1][0] * coefs[2][1] * coefs[0][2]
    ) - (
        coefs[2][0] * coefs[1][1] * coefs[0][2] +
        coefs[1][0] * coefs[0][1] * coefs[2][2] +
        coefs[0][0] * coefs[1][2] * coefs[2][1]
    );
}

Matrix Matrix::getCompanionMatrix()
{
    int m[SIZE][SIZE];
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            m[i][j] = pow(-1, i + j) * calcMinorDeterminant(MatrixPoint{(int) i,(int) j});
        }

    }

}

void Matrix::test()
{
    std::cout << calcMinorDeterminant(MatrixPoint{2, 1}) << std::endl;
}

int Matrix::calcOffset(int currOffset)
{
    if (currOffset > SIZE - 1)
    {
        return currOffset - SIZE;
    }

    return currOffset;
}

int Matrix::calcMinorDeterminant(const MatrixPoint & matrixPoint)
{
    if ((matrixPoint.x == SIZE || matrixPoint.x == 0) && (matrixPoint.y == SIZE || matrixPoint.y == 0))
    {
        return coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 1)] * coefs[calcOffset(matrixPoint.x + 2)][calcOffset(matrixPoint.y + 2)] - coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 2)] * coefs[calcOffset(matrixPoint.x + 2)][calcOffset(matrixPoint.y + 1)];
    }

    if ((matrixPoint.x == 1 && matrixPoint.y == 1))
    {
        return coefs[0][0] * coefs[2][2] - coefs[0][2] * coefs[2][0];
    }

    std::cout << coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 1)] << std::endl;
    std::cout << std::endl;
    std::cout << calcOffset(matrixPoint.x + 1) << std::endl;
    std::cout << calcOffset(matrixPoint.y + 1) << std::endl;
    std::cout << "Property: " << coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 1)] << std::endl;

    std::cout << "Jebug ends" << std::endl;

    return -1 * (
        coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 1)] *
        coefs[calcOffset(matrixPoint.x + 2)][calcOffset(matrixPoint.y + 2)] -
        coefs[calcOffset(matrixPoint.x + 1)][calcOffset(matrixPoint.y + 2)] *
        coefs[calcOffset(matrixPoint.x + 2)][calcOffset(matrixPoint.y + 1)]);
}
