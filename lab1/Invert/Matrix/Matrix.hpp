#pragma once
#include <vector>

class Matrix
{
private:
    const static int SIZE = 3;

    int coefs[SIZE][SIZE];
public:
    Matrix(std::vector<std::vector<int>>* m);
    int calcDeterminant();
};
