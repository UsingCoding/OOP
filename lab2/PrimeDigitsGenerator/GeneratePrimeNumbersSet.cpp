#include "./GeneratePrimeNumbersSet.hpp"

#include <vector>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <iostream>

#include "../../Utils/StringUtils.hpp"

const int MAX_ELEM = 1e8;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    if (upperBound > MAX_ELEM)
    {
        throw std::logic_error(StringUtils::StringConcatenator() << "Upper bound more than " << MAX_ELEM);
    }

    if (upperBound < 0)
    {
        throw std::logic_error("You must provide non-negative value");
    }
    
    
    std::vector<bool> sieve(upperBound + 1);
    std::set<int> result;

    sieve[0] = sieve[1] = true;

    for (int i = 2; i <= (int) sqrt(upperBound); i++)
    {
        if (sieve[i])
        {
            continue;
        }
        
        int it = pow(i, 2);
        while (it <= upperBound)
        {
            sieve[it] = true;
            it += i;
        }
    }
    
    for (int i = 0; i < upperBound + 1; i++)
    {
        if (!sieve[i])
        {
            result.insert(i);
        }
    }
    
    
    return result;
}