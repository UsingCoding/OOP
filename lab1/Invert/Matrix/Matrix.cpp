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

Matrix* Matrix::GetInverseMatrix()
{
    float deter = CalcDeterminant();

    if ((int) deter == 0)
    {
        return nullptr;
    }


    Matrix* matrix = GetCompanionMatrix();

    *matrix *= 1.0 / deter;

    return matrix;
}

float Matrix::CalcDeterminant()
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

Matrix* Matrix::GetCompanionMatrix()
{
    std::vector<std::vector<float>> m;
    for (size_t i = 0; i < SIZE; i++)
    {
        m.push_back(std::vector<float>{0, 0, 0});
        for (size_t j = 0; j < SIZE; j++)
        {
            m[i][j] = pow(-1, i + j) * CalcMinorDeterminant(MatrixPoint{(int) i,(int) j});
        }

    }
    return new Matrix(&m);
}

int Matrix::CalcOffset(int currOffset)
{
    if (currOffset > SIZE - 1)
    {
        return currOffset - SIZE;
    }

    return currOffset;
}

float Matrix::CalcMinorDeterminant(const MatrixPoint & matrixPoint)
{
    if ((matrixPoint.x == SIZE - 1 || matrixPoint.x == 0) && (matrixPoint.y == SIZE - 1 || matrixPoint.y == 0))
    {
        return coefs[CalcOffset(matrixPoint.y + 1)][CalcOffset(matrixPoint.x + 1)] *
        coefs[CalcOffset(matrixPoint.y + 2)][CalcOffset(matrixPoint.x + 2)] -
        coefs[CalcOffset(matrixPoint.y + 2)][CalcOffset(matrixPoint.x + 1)] *
        coefs[CalcOffset(matrixPoint.y + 1)][CalcOffset(matrixPoint.x + 2)];
    }

    if ((matrixPoint.x == 1 && matrixPoint.y == 1))
    {
        return coefs[0][0] * coefs[2][2] - coefs[0][2] * coefs[2][0];
    }

    return -1 * (
        coefs[CalcOffset(matrixPoint.y + 1)][CalcOffset(matrixPoint.x + 1)] *
        coefs[CalcOffset(matrixPoint.y + 2)][CalcOffset(matrixPoint.x + 2)] -
        coefs[CalcOffset(matrixPoint.y + 2)][CalcOffset(matrixPoint.x + 1)] *
        coefs[CalcOffset(matrixPoint.y + 1)][CalcOffset(matrixPoint.x + 2)]);
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

void Matrix::PrintMatrix()
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            std::cout << coefs[i][j];
            if (j != SIZE -1)
            {
                std::cout << ' ';
            }

        }
        std::cout << std::endl;
    }
}
