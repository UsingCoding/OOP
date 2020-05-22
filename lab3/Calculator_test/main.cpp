#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

#include "../Calculator/NodeBuilder/NodeBuilder.hpp"
#include "../Calculator/Parser/Parser.hpp"
#include "../Calculator/Infrastructure/ResourceManger/ResourceManager.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Variable.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Function.hpp"

#include "../Calculator/Interpreter/Interpreter.hpp"

SCENARIO("Calculating two functions")
{
    GIVEN("Interpreter")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);
        std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(nodeBuilder, manager);

        AND_GIVEN("Two variables: first is defined, second is not defined")
        {
            std::string req = "let number_1 = 4";
            interpreter->Handle(req);

            req = "var number_2";
            interpreter->Handle(req);

            THEN("We retrieve varibale value and it`s NaN")
            {
                req = "print number_2";
                std::string res = interpreter->Handle(req);
                REQUIRE(res == "NaN");
            }

            AND_WHEN("We define function with params number_1 - number_2")
            {
                std::string req = "fn function = number_1 - number_2";
                interpreter->Handle(req);

                THEN("We check value of function and it`s NaN")
                {
                    req = "print function";
                    std::string res = interpreter->Handle(req);
                    REQUIRE(res == "NaN");
                }

                AND_WHEN("We define second variable")
                {
                    req = "let number_2 = 5";
                    interpreter->Handle(req);

                    THEN("We check function value")
                    {
                        req = "print function";
                        std::string res = interpreter->Handle(req);
                        REQUIRE(res == "-1");
                    }

                    AND_WHEN("We define new variable and new function")
                    {
                        req = "let number_3 = 15";
                        interpreter->Handle(req);

                        req = "fn sum = function + number_3";
                        interpreter->Handle(req);

                        THEN("We retrieve value of this func")
                        {
                            req = "print sum";
                            std::string res = interpreter->Handle(req);
                            REQUIRE(res == "14");
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Trying to calculate recursive function")
{
    GIVEN("Gentelman kit(empty resourses)")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);
        std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(nodeBuilder, manager);

        WHEN("We define function and use it in itself")
        {
            std::string req = "fn function = function - function";
            std::string res = interpreter->Handle(req);

            THEN("We have exception that function is not defined")
            {
                REQUIRE(res == "No variable or function by this identificator exist: function");
            }
        }
    }
}

SCENARIO("Declare and define variables in different cases and without spaces between words and symbols")
{
    GIVEN("Gentelman kit(interpreter)")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);
        std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(nodeBuilder, manager);

        WHEN("We declare variable in incorrect way we have error")
        {
            std::string req = "varchar";

            std::string res = interpreter->Handle(req);

            REQUIRE(res == "Unknown terminal varchar");
        }

        WHEN("We define variable without spaces between sign")
        {
            std::string req = "let number=4";

            std::string res = interpreter->Handle(req);

            REQUIRE(res == "Success");
        }

        WHEN("We declare some variable")
        {
            std::string req = "var number";
            interpreter->Handle(req);

            AND_WHEN("We define same variable name with letter in uppercase")
            {
                req = "let NUMBER = 4";
                std::string res = interpreter->Handle(req);

                THEN("We got no errors")
                {
                    REQUIRE(res == "Success");
                }

                AND_WHEN("We try to get value of var")
                {
                    req = "print number";
                    std::string res = interpreter->Handle(req);

                    THEN("We got NaN")
                    {
                        REQUIRE(res == "NaN");
                    }
                }
            }
        }
    }
}

SCENARIO("Calculating Fibonacci number 8 and change first number")
{
    GIVEN("Interpreter")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);
        std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(nodeBuilder, manager);

        AND_GIVEN("Defined variables and functions")
        {

            std::vector<std::string> commands = {
                "let v0=0",
                "let v1=1",
                "fn fib0=v0",
                "fn fib1=v1",
                "fn fib2=fib1+fib0",
                "fn fib3=fib2+fib1",
                "fn fib4=fib3+fib2",
                "fn fib5=fib4+fib3",
                "fn fib6=fib5+fib4",
                "fn fib7=fib6+fib5",
                "fn fib8=fib7+fib6",
            };

            std::for_each(commands.begin(), commands.end(), [&interpreter](std::string command){
                interpreter->Handle(command);
            });



            THEN("We get number 8")
            {
                std::string req = "print fib8";
                std::string res = interpreter->Handle(req);

                REQUIRE("21" == res);
            }

            AND_WHEN("We change v1 to 2")
            {
                std::string req = "let v1= 2";
                interpreter->Handle(req);

                THEN("We have number 8 is equal to ")
                {
                    req = "print fib8";
                    std::string res = interpreter->Handle(req);

                    REQUIRE(res == "42");
                }
            }
        }
    }
}

SCENARIO("Defining incorrect-named variable, function with three params, and using in function unknown variable, and calculating function with one undefined argument")
{
    GIVEN("Interpreter")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);
        std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(nodeBuilder, manager);

        WHEN("We try to define incorrect-named variable")
        {
            std::string req = "let 1number = 4";
            std::string res = interpreter->Handle(req);

            THEN("We got error response")
            {
                REQUIRE(res == "Incorrect name for identificator");
            }
        }

        WHEN("We try to define function with 3 params")
        {
            std::string req = "fn function = number_1 + number_2 + number_3";
            std::string res = interpreter->Handle(req);

            THEN("We got error response")
            {
                REQUIRE(res == "Incorrect function declaration");
            }
        }

        AND_GIVEN("Variable with some value")
        {
            std::string req = "let number = 4";
            interpreter->Handle(req);

            WHEN("We defining function with unknown param")
            {
                std::string req = "fn function = var_2 + number";
                std::string res = interpreter->Handle(req);

                THEN("We got error response")
                {
                    REQUIRE(res == "No variable or function by this identificator exist: var_2");
                }
            }

            AND_GIVEN("Another variable without value")
            {
                std::string req = "var secondNumber";
                interpreter->Handle(req);

                WHEN("We define a function with this variables")
                {
                    std::string req = "fn function = number - secondNumber";
                    std::string res = interpreter->Handle(req);

                    THEN("Function defined")
                    {
                        REQUIRE(res == "Success");
                    }

                    WHEN("We retrieving value of this function")
                    {
                        req = "print function";
                        res = interpreter->Handle(req);

                        THEN("We got NaN")
                        {
                            REQUIRE(res == "NaN");
                        }
                    }
                }
            }

            AND_GIVEN("Variable with zero value")
            {
                std::string req = "let zero = 0";
                interpreter->Handle(req);

                WHEN("We try to divide smth on zero variable")
                {
                    std::string req = "fn function = number / zero";
                    std::string res = interpreter->Handle(req);

                    THEN("We define a function, but her value is not calculated")
                    {
                        REQUIRE(res == "Success");
                    }

                    AND_WHEN("We calculate this function")
                    {
                        std::string req = "print function";
                        std::string res = interpreter->Handle(req);

                        THEN("We got an error")
                        {
                            REQUIRE(res == "You can`t divide by zero");
                        }
                    }
                }
            }
        }
    }
}
