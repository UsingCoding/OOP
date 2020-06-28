#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(const std::vector<T> & arr, T & maxValue, const Less & less)
{
    if (arr.size() == 0)
    {
        return false;
    }

    size_t indexOfMax = 0;
    for (auto i = 1; i < arr.size(); i++)
    {
        if (!less(arr[i], arr[indexOfMax]))
        {
            indexOfMax = i;
        }
    }

    maxValue = arr[indexOfMax];
    return true;
}
