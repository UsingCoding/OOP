#pragma once
#include <vector>

class Matrix
{
public:
    const static int SIZE = 3;

    Matrix(std::vector<std::vector<float>>* m);
    float CalcDeterminant();
    Matrix* GetCompanionMatrix();
    void operator *= (float coef);

    Matrix* GetInverseMatrix();
    void PrintMatrix();

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
