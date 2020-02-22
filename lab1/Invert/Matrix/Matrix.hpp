#pragma once
#include <vector>

class Matrix
{
private:
    const static int SIZE = 3;

    struct MatrixPoint
    {
        int x;
        int y;
    };

    int coefs[SIZE][SIZE];
    int calcMinorDeterminant(const MatrixPoint & matrixPoint);
    int calcOffset(int currOffset);
public:
    Matrix(std::vector<std::vector<int>>* m);
    int calcDeterminant();
    Matrix getCompanionMatrix();
    void test();
};
