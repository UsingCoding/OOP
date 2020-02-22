#include "./Matrix.hpp"
#include <iostream>
#include <cmath>
#include <vector>

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

// Matrix::Matrix(int* m[SIZE][SIZE])
// {
//     coefs = (*m);
// }

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

Matrix* Matrix::getCompanionMatrix()
{
    // int m[SIZE][SIZE];
    std::vector<std::vector<int>> m;
    for (size_t i = 0; i < SIZE; i++)
    {
        m.push_back(std::vector<int>{0, 0, 0});
        for (size_t j = 0; j < SIZE; j++)
        {
            m[i][j] = pow(-1, i + j) * calcMinorDeterminant(MatrixPoint{(int) i,(int) j});
        }

    }

    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            std::cout << m[j][i] << ' ';
        }
        std::cout << std::endl;

    }

    return new Matrix(&m);
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
    if ((matrixPoint.x == SIZE - 1 || matrixPoint.x == 0) && (matrixPoint.y == SIZE - 1 || matrixPoint.y == 0))
    {
        return coefs[calcOffset(matrixPoint.y + 1)][calcOffset(matrixPoint.x + 1)] *
        coefs[calcOffset(matrixPoint.y + 2)][calcOffset(matrixPoint.x + 2)] -
        coefs[calcOffset(matrixPoint.y + 2)][calcOffset(matrixPoint.x + 1)] *
        coefs[calcOffset(matrixPoint.y + 1)][calcOffset(matrixPoint.x + 2)];
    }

    if ((matrixPoint.x == 1 && matrixPoint.y == 1))
    {
        return coefs[0][0] * coefs[2][2] - coefs[0][2] * coefs[2][0];
    }

    return -1 * (
        coefs[calcOffset(matrixPoint.y + 1)][calcOffset(matrixPoint.x + 1)] *
        coefs[calcOffset(matrixPoint.y + 2)][calcOffset(matrixPoint.x + 2)] -
        coefs[calcOffset(matrixPoint.y + 2)][calcOffset(matrixPoint.x + 1)] *
        coefs[calcOffset(matrixPoint.y + 1)][calcOffset(matrixPoint.x + 2)]);
}
