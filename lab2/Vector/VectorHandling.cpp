#include "./VectorHandling.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>

void HandleVector(std::vector<int> & vector)
{
    int sumOfNeg = std::accumulate(vector.begin(), vector.end(), 0, [](int sum, int value){
        if (value >= 0)
        {
            sum += value;
        }

        return sum;
    });

    bool odd = true;
    std::transform(vector.begin(), vector.end(), vector.begin(), [&sumOfNeg, &odd](int value) -> int {
        if (odd)
        {
            odd = false;
            return value -= sumOfNeg;
        }
        else
        {
            odd = true;
            return value *= 2;
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
