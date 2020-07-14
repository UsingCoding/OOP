#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../StringStack/Stack/Stack.hpp"

#include <string>

SCENARIO("Creating StringStack and pushing elements there")
{
    GIVEN("StringStack")
    {
        StringStack stack;

        WHEN("We adding element")
        {
            THEN("We have no errors")
            {
                REQUIRE_NOTHROW(stack.Push("Stack pushed"));

                AND_WHEN("We pop element")
                {
                    THEN("We have no errors")
                    {
                        std::string value;
                        REQUIRE_NOTHROW(value = stack.Pop());
                        REQUIRE(value == "Stack pushed");
                    }
                }
            }
        }
    }
}

SCENARIO("Creating a StringStack and moving, and copying it")
{
    GIVEN("String stack with two elements")
    {
        StringStack stack;
        stack.Push("Stack is not empty");
        stack.Push("Stack pushed");

        WHEN("We copying stack in constructor")
        {
            bool wasError = false;

            try
            {
                StringStack copyStack = stack;

                AND_WHEN("We pop value from copy")
                {
                    std::string valueFromCopy;
                    REQUIRE_NOTHROW(valueFromCopy = copyStack.Pop());

                    THEN("Stack size of original didn`t change")
                    {
                        std::string valueFromOriginal;
                        REQUIRE_NOTHROW(valueFromOriginal = stack.Pop());

                        AND_THEN("Values from original and copy is equal")
                        {
                            REQUIRE(valueFromOriginal == valueFromCopy);
                        }
                    }
                }
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }

            REQUIRE_FALSE(wasError);
        }

        WHEN("We copying stack")
        {
            StringStack copyStack;
            REQUIRE_NOTHROW(copyStack = stack);

            AND_WHEN("We pop value from copy")
            {
                std::string valueFromCopy;
                REQUIRE_NOTHROW(valueFromCopy = copyStack.Pop());

                THEN("Stack size of original didn`t change")
                {
                    std::string valueFromOriginal;
                    REQUIRE_NOTHROW(valueFromOriginal = stack.Pop());

                    AND_THEN("Values from original and copy is equal")
                    {
                        REQUIRE(valueFromOriginal == valueFromCopy);
                    }
                }
            }
        }

        WHEN("We moving data ownership in constructor")
        {
            bool wasError = false;

            try
            {
                StringStack newOwner = std::move(stack);

                THEN("newOwner has data and size = 1, but prev owner has no data and throws exception")
                {
                    REQUIRE_NOTHROW(newOwner.Pop());
                    REQUIRE_THROWS(stack.Pop());
                }
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }

            REQUIRE_FALSE(wasError);
        }

        WHEN("We moving stack")
        {
            StringStack newOwner;
            REQUIRE_NOTHROW(newOwner = std::move(stack));

            THEN("newOwner has data and size = 1, but prev owner has no data and throws exception")
            {
                REQUIRE_NOTHROW(newOwner.Pop());
                REQUIRE_THROWS(stack.Pop());
            }
        }
    }
}
