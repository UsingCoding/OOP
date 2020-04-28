#include<iostream>

#include "GeneratePrimeNumbersSet.hpp"
#include <set>

int main(int argc, char const *argv[])
{
    std::set<int> result = GeneratePrimeNumbersSet(1e8);

    // for (std::set<int>::iterator it = result.begin(); it != result.end(); it++) {
    //     std::cout << *it << " ";
    // }

    std::cout << std::endl << result.size() << std::endl; 
    
    return 0;
}
