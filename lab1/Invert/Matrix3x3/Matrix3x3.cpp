#include "./Matrix3x3.hpp"
#include <iostream>
#include <cmath>

Matrix3x3::Matrix3x3(const std::array<std::array<float, SIZE>, SIZE> & matrix)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            coefs[i][j] = matrix[i][j];
        }
    }
}

std::unique_ptr<Matrix3x3> Matrix3x3::GetInverseMatrix() const
{
    float deter = CalcDeterminant();

    if ((int) deter == 0)
    {
        return nullptr;
    }

    std::unique_ptr<Matrix3x3> matrix = GetCompanionMatrix();

    *matrix *= 1.0 / deter;

    return matrix;
}

float Matrix3x3::CalcDeterminant() const
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

std::unique_ptr<Matrix3x3> Matrix3x3::GetCompanionMatrix() const
{
    std::array<std::array<float, SIZE>, SIZE> matrix;
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            matrix[i][j] = pow(-1, i + j) * CalcMinorDeterminant(MatrixPoint{(int) i,(int) j});
        }
    }
    return std::unique_ptr<Matrix3x3>(new Matrix3x3(matrix));
}

int Matrix3x3::CalcOffsetInMinor(int currOffset)
{
    return currOffset > SIZE - 1 ? currOffset - SIZE : currOffset;
}

float Matrix3x3::CalcMinorDeterminant(const MatrixPoint & matrixPoint) const
{
    if ((matrixPoint.x == SIZE - 1 || matrixPoint.x == 0) && (matrixPoint.y == SIZE - 1 || matrixPoint.y == 0))
    {
        return coefs[CalcOffsetInMinor(matrixPoint.y + 1)][CalcOffsetInMinor(matrixPoint.x + 1)] *
        coefs[CalcOffsetInMinor(matrixPoint.y + 2)][CalcOffsetInMinor(matrixPoint.x + 2)] -
        coefs[CalcOffsetInMinor(matrixPoint.y + 2)][CalcOffsetInMinor(matrixPoint.x + 1)] *
        coefs[CalcOffsetInMinor(matrixPoint.y + 1)][CalcOffsetInMinor(matrixPoint.x + 2)];
    }

    if ((matrixPoint.x == 1 && matrixPoint.y == 1))
    {
        return coefs[0][0] * coefs[2][2] - coefs[0][2] * coefs[2][0];
    }

    return -1 * (
        coefs[CalcOffsetInMinor(matrixPoint.y + 1)][CalcOffsetInMinor(matrixPoint.x + 1)] *
        coefs[CalcOffsetInMinor(matrixPoint.y + 2)][CalcOffsetInMinor(matrixPoint.x + 2)] -
        coefs[CalcOffsetInMinor(matrixPoint.y + 2)][CalcOffsetInMinor(matrixPoint.x + 1)] *
        coefs[CalcOffsetInMinor(matrixPoint.y + 1)][CalcOffsetInMinor(matrixPoint.x + 2)]);
}


void Matrix3x3::operator *= (float coef)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            coefs[i][j] *= coef;
        }
    }
}

std::ostream& operator << (std::ostream &out, const Matrix3x3 & matrix)
{
    for (size_t i = 0; i < Matrix3x3::SIZE; i++)
    {
        for (size_t j = 0; j < Matrix3x3::SIZE; j++)
        {
            out << matrix.coefs[i][j];
            if (j != Matrix3x3::SIZE -1)
            {
                out << ' ';
            }
        }
        out << std::endl;
    }
}
