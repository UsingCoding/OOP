#pragma once
#include <vector>

class Matrix
{
public:
    const static int SIZE = 3;

    Matrix(std::vector<std::vector<float>>* m);
    float calcDeterminant();
    Matrix* getCompanionMatrix();
    void operator *= (float coef);

    Matrix* getInverseMatrix();
    void printMatrix();

private:
    struct MatrixPoint
    {
        int x;
        int y;
    };

    float coefs[SIZE][SIZE];
    float calcMinorDeterminant(const MatrixPoint & matrixPoint);
    int calcOffset(int currOffset);
};
