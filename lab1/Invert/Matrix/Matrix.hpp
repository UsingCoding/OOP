#pragma once
#include <vector>
#include <iostream>

class Matrix
{
public:
    const static int SIZE = 3;

    Matrix(std::vector<std::vector<float>>* m);
    void operator *= (float coef);
    friend std::ostream& operator<< (std::ostream &out, const Matrix matrix);

    float CalcDeterminant();
    Matrix* GetCompanionMatrix();
    Matrix* GetInverseMatrix();

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
