#include "./Matrix.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

Matrix::Matrix(std::vector<std::vector<float>>* m)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            coefs[i][j] = (*m)[i][j];
        }
    }

}

Matrix* Matrix::getInverseMatrix()
{
    float deter = calcDeterminant();

    if ((int) deter == 0)
    {
        return nullptr;
    }


    Matrix* matrix = getCompanionMatrix();

    *matrix *= 1.0 / deter;

    return matrix;
}

float Matrix::calcDeterminant()
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
    std::vector<std::vector<float>> m;
    for (size_t i = 0; i < SIZE; i++)
    {
        m.push_back(std::vector<float>{0, 0, 0});
        for (size_t j = 0; j < SIZE; j++)
        {
            m[i][j] = pow(-1, i + j) * calcMinorDeterminant(MatrixPoint{(int) i,(int) j});
        }

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

float Matrix::calcMinorDeterminant(const MatrixPoint & matrixPoint)
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


void Matrix::operator *= (float coef)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            coefs[i][j] *= coef;
        }
    }
}

void Matrix::printMatrix()
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            std::cout << coefs[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
