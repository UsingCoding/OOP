#include "./VectorHandling.hpp"
#include <iostream>
#include <algorithm>

void HandleVector(std::vector<int> & vector)
{
    int sumOfNeg = 0;
    std::for_each(vector.begin(), vector.end(), [&sumOfNeg](int value) {
        if (value >= 0)
        {
            sumOfNeg += value;
        }
    });


    bool odd = true;
    std::for_each(vector.begin(), vector.end(), [&sumOfNeg, &odd](int & value) {
        if (odd)
        {
            value -= sumOfNeg;
            odd = false;
        }
        else
        {
            value *= 2;
            odd = true;
        }
    });
}

void SortVector(std::vector<int> & vector)
{
    std::sort(vector.begin(), vector.end());
}

void HandleAndSortVector(std::vector<int> & vector)
{
    HandleVector(vector);
    SortVector(vector);
}