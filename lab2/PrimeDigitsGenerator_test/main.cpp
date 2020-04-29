#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <set>

#include "../PrimeDigitsGenerator/GeneratePrimeNumbersSet.hpp"

SCENARIO("Set of prime numbers up to 4")
{
    REQUIRE(GeneratePrimeNumbersSet(4) == std::set<int>{2, 3});
}

SCENARIO("Set of prime numbers up to 0")
{
    REQUIRE(GeneratePrimeNumbersSet(0) == std::set<int>{});
}

SCENARIO("Set of prime numbers up to 1")
{
    REQUIRE(GeneratePrimeNumbersSet(1) == std::set<int>{});
}

SCENARIO("Set of prime numbers up to -1")
{
    WHEN("We try to calculate set of prime numbers up to -1")
    {
        int upperBound = -1;
        THEN("Function throws an error")
        {
            bool result;
            try
            {
                GeneratePrimeNumbersSet(upperBound);
                result = false;
            }
            catch(const std::exception& e)
            {
                result = true;
            }
            
            REQUIRE(result);
        }
    }
}

SCENARIO("Try to calculate set of prime numbers up to more than max value")
{
    WHEN("We try to calculate set of prime numbers up to 1e9")
    {
        int upperBound = 1e9;
        THEN("Function throws an error")
        {
            bool result;
            try
            {
                GeneratePrimeNumbersSet(upperBound);
                result = false;
            }
            catch(const std::exception& e)
            {
                result = true;
            }
            
            REQUIRE(result);
        }
    }
}

SCENARIO("Count of prime numbers up to 1000")
{
    REQUIRE(GeneratePrimeNumbersSet(1000).size() == 168);
}

SCENARIO("Count of prime numbers up to 1e8")
{
    REQUIRE(GeneratePrimeNumbersSet(1e8).size() == 5761455);
}

