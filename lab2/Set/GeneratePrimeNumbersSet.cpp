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
        if (sieve[i] == true)
        {
            continue;
        }
        
        int it = 2;
        while (i * it <= upperBound)
        {
            sieve[i * it] = true;
            it += 1;
        }
    }
    
    for (unsigned int i = 0; i < upperBound + 1; i++)
    {
        if (sieve[i] == false)
        {
            result.insert(i);
        }
    }
    
    
    return result;
}