#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

#include "../FindMaxEx/FindMaxEx/FindMaxEx.hpp"

template<class T>
class Functor
{
public:
    Functor() {}
    bool operator()(const T a, const T b) const
    {
        return a > b;
    }
};

SCENARIO("Find max in int array and in empty array")
{
    GIVEN("Array of integers and res value")
    {
        std::vector<int> arr{1, 4, 5, 2, 3, 23, 2};

        int resVal;

        WHEN("We launch func to find max el")
        {
            bool res = FindMax(arr, resVal, [](int a, int b) { return a < b; });

            THEN("We got true as func result and max value written in resVale")
            {
                REQUIRE(res);
                REQUIRE(resVal == 23);
            }
        }
    }

    GIVEN("Empty array")
    {
        std::vector<int> arr;

        int resVal = -1;

        WHEN("We launch func to find max el")
        {
            bool res = FindMax(arr, resVal, [](int a, int b) { return a < b; });

            THEN("We go false as func result and resVal doesn`t changed")
            {
                REQUIRE_FALSE(res);
                REQUIRE(resVal == -1);
            }
        }
    }
}

SCENARIO("Sending to function a functor")
{
    GIVEN("Functor instance and array")
    {
        Functor<int> functor;

        std::vector<int> arr{1, 4, 5, 2, 3, 23, 2};

        int resVal;

        WHEN("We use functor to find element")
        {
            bool res = FindMax(arr, resVal, functor);

            THEN("We got true as res and resVal equal to smallest num")
            {
                REQUIRE(res);
                REQUIRE(resVal == 1);
            }
        }
    }
}
