#include <iostream>
#include <vector>
#include "./VectorHandling.hpp"

int main(int argc, char const *argv[])
{
    std::vector<int> vector = {1, 2, 3, -4, 12, -7};

    HandleAndSortVector(vector);

    return 0;
}