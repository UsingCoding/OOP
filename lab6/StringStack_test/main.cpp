#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../StringStack/Stack/Stack.hpp"

SCENARIO("Creating StringStack and pushing elements there")
{
    GIVEN("StringStack")
    {
        Stack<int> stack;

        WHEN("We adding element")
        {
            THEN("We have no errors")
            {
                REQUIRE_NOTHROW(stack.Push(4));

                AND_WHEN("We pop element")
                {
                    THEN("We have no errors")
                    {
                        REQUIRE_NOTHROW(stack.Pop());
                    }
                }
            }
        }
    }
}

SCENARIO("Creating a StringStack and moving, and copying it")
{
    GIVEN("String stack with element")
    {
        Stack<int> stack;
        stack.Push(4);

        WHEN("We copying stack in constructor")
        {
            bool wasError = false;

            try
            {
                Stack<int> copyStack = stack;

                AND_WHEN("We pop value from copy")
                {
                    REQUIRE_NOTHROW(copyStack.Pop());

                    THEN("Stack size of original didn`t change")
                    {
                        REQUIRE_NOTHROW(stack.GetSize() == 1);
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
            Stack<int> copyStack;
            REQUIRE_NOTHROW(copyStack = stack);

            AND_WHEN("We pop value from copy")
            {
                REQUIRE_NOTHROW(copyStack.Pop());

                THEN("Stack size of original didn`t change")
                {
                    REQUIRE_NOTHROW(stack.GetSize() == 1);
                }
            }
        }

        WHEN("We moving data ownership in constructor")
        {
            bool wasError = false;

            try
            {
                Stack<int> newOwner = std::move(stack);

                THEN("newOwner has data and size = 1, but prev owner has no data")
                {
                    REQUIRE(newOwner.GetSize() == 1);
                    REQUIRE(stack.GetSize() == 0);
                    REQUIRE_NOTHROW(newOwner.Pop());
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
            Stack<int> newOwner;
            REQUIRE_NOTHROW(newOwner = std::move(stack));

            THEN("newOwner has data and size = 1, but prev owner has no data")
            {
                REQUIRE(newOwner.GetSize() == 1);
                REQUIRE(stack.GetSize() == 0);
                REQUIRE_NOTHROW(newOwner.Pop());
            }
        }
    }
}
