#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

#include "../Vector/VectorHandling.hpp"

SCENARIO("Handle vector with empty vector")
{
    std::vector<int> emptyVector = {};
    HandleAndSortVector(emptyVector);
    REQUIRE(emptyVector.size() == 0);
}

SCENARIO("Handle vector with with one non-negative number")
{
    std::vector<int> oneNumberVector = {1};
    HandleAndSortVector(oneNumberVector);
    REQUIRE(oneNumberVector == std::vector<int>{0});
}

SCENARIO("Handle vector with with one negative number")
{
    std::vector<int> oneNumberVector = {-4};
    HandleAndSortVector(oneNumberVector);
    REQUIRE(oneNumberVector == std::vector<int>{-4});
}


SCENARIO("Handle vector with vector where no non-positive numbers")
{
    std::vector<int> negativeNumbersVector = {-1, -2, -3, -4, -5};
    HandleAndSortVector(negativeNumbersVector);
    REQUIRE(negativeNumbersVector == std::vector<int>{-8, -5, -4, -3, -1});
}

SCENARIO("Handle vector with 0 on even positions")
{
    std::vector<int> positiveNumbersVector = {1, 0, 3, 0, 5};
    HandleAndSortVector(positiveNumbersVector);
    REQUIRE(positiveNumbersVector == std::vector<int>{-8, -6, -4, 0, 0});
}

SCENARIO("Sort vector ascending")
{
    std::vector<int> positiveNumbersVector = {1, 0, 3, 0, 5};
    SortVector(positiveNumbersVector);
    REQUIRE(positiveNumbersVector == std::vector<int>{0, 0, 1, 3, 5});
}

SCENARIO("Handling vector without sorting")
{
    std::vector<int> vector = {1, 0, 3, 0, 5};
    HandleVector(vector);
    REQUIRE(vector == std::vector<int>{-8, 0, -6, 0, -4});
}
