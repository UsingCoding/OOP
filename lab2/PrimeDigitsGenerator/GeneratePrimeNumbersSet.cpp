#include "./GeneratePrimeNumbersSet.hpp"

#include <vector>
#include <exception>
#include <math.h>
#include <algorithm>

#include <iostream>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    if (upperBound > MAX_ELEM)
    {
        // throw std::logic_error();
    }
    
    // Элементы, у которых значение true, исключены из решета
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
    
    for (unsigned int i = 0; i < upperBound + 1; i++)
    {
        if (!sieve[i])
        {
            result.insert(i);
        }
    }
    
    
    return result;
}