#pragma once
#include <iostream>

template <typename T>
class Matrix
{
private:
    const static int SIZE = 3;

    T coefs[SIZE][SIZE] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
public:
    // Matrix(T (*m)[3])
    // {
    // }
    Matrix()
    {};
    int calcDeterminant();
};

template <typename T>
int Matrix<T>::calcDeterminant()
{
    std::cout << coefs[1][2] << std::endl;
    return (
        coefs[0][0] * coefs[1][1] * coefs[2][0] +
        coefs[2][0] * coefs[0][1] * coefs[1][2] +
        coefs[1][0] * coefs[2][1] * coefs[0][2]
    ) - (
        coefs[2][0] * coefs[1][1] * coefs[0][2] +
        coefs[1][0] * coefs[0][1] * coefs[2][2] +
        coefs[0][0] * coefs[1][2] * coefs[2][1]
    );
}
