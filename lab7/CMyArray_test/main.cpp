#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../CMyArray/MyArray/MyArray.hpp"

SCENARIO("Creating empty array templated by double")
{
    MyArray<double> array;

    WHEN("We push new value")
    {
        REQUIRE_NOTHROW(array.Push(4.4));

        THEN("Lenght of array become 1 and at zero position we got our value")
        {
            REQUIRE(array.GetSize() == 1);
            REQUIRE(array[0] == 4.4);
        }
    }

    WHEN("We add many values to array")
    {
        REQUIRE_NOTHROW(array.Push(4.4));
        REQUIRE_NOTHROW(array.Push(5.5));
        REQUIRE_NOTHROW(array.Push(1.4));
        REQUIRE_NOTHROW(array.Push(2.3));

        AND_WHEN("Trying to acces to index more than lenght - 1 of array we have an exception")
        {
            THEN("We got and exception")
            {
                REQUIRE_THROWS(array[5]);
            }
        }

        AND_WHEN("We resize array to 2")
        {
            REQUIRE_NOTHROW(array.Resize(2));

            THEN("Length of array now is 2 and we loose other values after second element")
            {
                REQUIRE(array.GetSize() == 2);
            }
        }

        AND_WHEN("When we clear array")
        {
            REQUIRE_NOTHROW(array.Clear());

            THEN("We got empty array")
            {
                REQUIRE(array.GetSize() == 0);
                REQUIRE_THROWS(array[0]);
            }
        }
    }
}

SCENARIO("Copying array and moving to other var")
{
    GIVEN("Array with three elements")
    {
        MyArray<double> array;
        REQUIRE_NOTHROW(array.Push(4.4));
        REQUIRE_NOTHROW(array.Push(5.5));
        REQUIRE_NOTHROW(array.Push(1.4));

        WHEN("We copy array to another by sending to constructor")
        {
            bool wasError = false;
            try
            {
                MyArray<double> excellentCopy(array);

                THEN("We got copy of the array")
                {
                    for (size_t i = 0; i < array.GetSize(); i++)
                    {
                        REQUIRE(excellentCopy[i] == array[i]);
                    }
                }
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }

            REQUIRE_FALSE(wasError);
        }

        WHEN("We assign our array to other arr")
        {
            MyArray<double> excellentCopy;
            REQUIRE_NOTHROW(excellentCopy = array);

            THEN("We got copy of array")
            {
                for (size_t i = 0; i < array.GetSize(); i++)
                {
                    REQUIRE(excellentCopy[i] == array[i]);
                }

                AND_WHEN("We change some value in array")
                {
                    array[2] = 4.0;

                    THEN("Value at same index in copy not changed")
                    {
                        REQUIRE_FALSE(array[2] == excellentCopy[2]);
                        REQUIRE(excellentCopy[2] == 1.4);
                    }
                }
            }
        }

        WHEN("We move array to dest in constructor")
        {
            MyArray<double> dest = std::move(array);

            THEN("We got array without content and dest with array data")
            {
                REQUIRE(array.GetSize() == 0);
                REQUIRE(dest.GetSize() == 3);
            }
        }

        WHEN("We move array to dest by assign operator")
        {
            MyArray<double> dest;
            REQUIRE(dest.GetSize() == 0);
            dest = std::move(array);

            THEN("We got array without content and dest with array data")
            {
                REQUIRE(array.GetSize() == 0);
                REQUIRE(dest.GetSize() == 3);
            }
        }
    }
}

SCENARIO("Iterate array forward and backward")
{
    GIVEN("Array with few elements")
    {
        MyArray<double> array;

        REQUIRE_NOTHROW(array.Push(4.4));
        REQUIRE_NOTHROW(array.Push(5.5));
        REQUIRE_NOTHROW(array.Push(1.4));

        WHEN("We iterate array forward")
        {
            THEN("We got elements in direct order")
            {
                int i = 0;
                for (auto it = array.begin(); it != array.end(); it++, i++)
                {
                    REQUIRE(*it == array[i]);
                }
            }
        }

        WHEN("We iterate array backward")
        {
            THEN("We got elements in reverse order")
            {
                int i = array.GetSize() - 1;
                for (auto it = array.rbegin(); it != array.rend(); it++, i--)
                {
                    REQUIRE(*it == array[i]);
                }
            }
        }
    }
}
