#pragma once

#include <vector>
#include <algorithm>

namespace VectorUtils
{
    template<class T>
    std::vector<T> Merge(const std::vector<T> & firstArg, const std::vector<T> & secondArg)
    {
        std::vector<T> result;

        std::for_each(firstArg.begin(), firstArg.end(), [&result](T arg){
            result.push_back(arg);
        });

        std::for_each(secondArg.begin(), secondArg.end(), [&result](T arg){
            result.push_back(arg);
        });

        return result;
    }

} // namespace VectorUtils
