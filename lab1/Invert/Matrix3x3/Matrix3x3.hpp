#pragma once
#include <vector>
#include <iostream>

class Matrix3x3
{
public:
    const static int SIZE = 3;

    Matrix3x3(const std::vector<std::vector<float>> & m);
    void operator *= (float coef);
    friend std::ostream& operator<< (std::ostream &out, const Matrix3x3* matrix);

    float CalcDeterminant();
    Matrix3x3* GetCompanionMatrix();
    Matrix3x3* GetInverseMatrix();

private:
    struct MatrixPoint
    {
        int x;
        int y;
    };

    float coefs[SIZE][SIZE];
    float CalcMinorDeterminant(const MatrixPoint & matrixPoint);
    int CalcOffset(int currOffset);
};
