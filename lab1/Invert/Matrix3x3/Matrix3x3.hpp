#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <memory>

class Matrix3x3
{
public:
    const static int SIZE = 3;

    Matrix3x3(const std::array<std::array<float, SIZE>, SIZE> & matrix);
    void operator *= (float coef);
    friend std::ostream& operator<< (std::ostream &out, const Matrix3x3 & matrix);

    float CalcDeterminant() const;
    std::unique_ptr<Matrix3x3> GetCompanionMatrix() const;
    std::unique_ptr<Matrix3x3> GetInverseMatrix() const;
private:
    struct MatrixPoint
    {
        int x;
        int y;
    };

    float coefs[SIZE][SIZE];
    float CalcMinorDeterminant(const MatrixPoint & matrixPoint) const;
    int static CalcOffsetInMinor(int currOffset);
};
