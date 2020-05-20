#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>
#include <memory>
#include <sstream>

#include "../Calculator/NodeBuilder/NodeBuilder.hpp"
#include "../Calculator/Parser/Parser.hpp"
#include "../Calculator/Infrastructure/ResourceManger/ResourceManager.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Variable.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Function.hpp"

void MakeRequest(std::unique_ptr<NodeBuilder> & nodeBuilder, const std::string & userInput)
{
    auto tokens = Parser::RetrieveTokensList(userInput);
    std::unique_ptr<NodeBuilderInput> input = Parser::BuildInput(tokens);
    nodeBuilder->MapIntoModels(*input);
}


SCENARIO("Declaring variable then defining her")
{
    GIVEN("An empty ResourceManager and NodeBuilder")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

        WHEN("We declare a new varibale")
        {
            std::string userInputToDeclareVariable = "var number";

            AND_WHEN("We parse user input")
            {
                auto res = Parser::RetrieveTokensList(userInputToDeclareVariable);
                std::string variableIdentificator = "number";

                THEN("We got user input divided by terminal characters")
                {
                    REQUIRE(res == std::vector<std::string>{"var", variableIdentificator});
                }

                AND_WHEN("We saving user variable")
                {
                    bool wasError = false;
                    std::unique_ptr<NodeBuilderInput> input;

                    try
                    {
                        input = Parser::BuildInput(res);
                    }
                    catch(const std::exception& e)
                    {
                        wasError = true;
                    }

                    REQUIRE(!wasError);

                    try
                    {
                        nodeBuilder->MapIntoModels(*input);
                    }
                    catch(const std::exception& e)
                    {
                        wasError = true;
                    }

                    REQUIRE(!wasError);

                    THEN("We check that variable declarated")
                    {

                        try
                        {
                            manager->RetrieveVariableByIdentificator(variableIdentificator);
                        }
                        catch(const std::exception& e)
                        {
                            wasError = true;
                        }

                        REQUIRE(!wasError);
                    }

                    AND_WHEN("We define variable")
                    {
                        std::string userInputToDefVar = "let number = 4";
                        auto tokens = Parser::RetrieveTokensList(userInputToDefVar);
                        input = Parser::BuildInput(tokens);
                        nodeBuilder->MapIntoModels(*input);
                        
                        THEN("We can retrieve this varibale")
                        {
                            try
                            {
                                manager->RetrieveVariableByIdentificator(variableIdentificator);
                            }
                            catch(const std::exception& e)
                            {
                                wasError = true;
                            }

                            REQUIRE(!wasError);
                        }
                    }

                }
            }
        }
    }
}

SCENARIO("Calculating two functions")
{
    GIVEN("Empty resourses")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

        AND_GIVEN("Two variables: first is defined, second is not defined")
        {
            std::string varIdentificator = "number_1";
            std::shared_ptr<Variable> var_1 = std::make_shared<Variable>();
            var_1->SetValue(4);
            manager->Add(varIdentificator, var_1);

            varIdentificator = "number_2";
            std::shared_ptr<Variable> var_2 = std::make_shared<Variable>();
            manager->Add(varIdentificator, var_2);

            THEN("We retrieve varibale value and it`s NaN")
            {
                std::shared_ptr<Variable> var = manager->RetrieveVariableByIdentificator(varIdentificator);
                REQUIRE((std::string) *var == "NaN");
            }

            AND_WHEN("We define function with params number_1 - number_2")
            {
                std::string req = "fn function = number_1 - number_2";
                MakeRequest(nodeBuilder, req);

                THEN("We check value of function and it`s NaN")
                {
                    std::shared_ptr<Function> func = manager->RetrieveFunctionByIdentificator("function");
                    REQUIRE((std::string) *func == "NaN");
                }

                AND_WHEN("We define second variable")
                {
                    req = "let number_2 = 5";
                    MakeRequest(nodeBuilder, req);

                    THEN("We check function value")
                    {
                        std::shared_ptr<Function> func = manager->RetrieveFunctionByIdentificator("function");
                        REQUIRE((std::string) *func == "-1");
                    }

                    AND_WHEN("We define new variable and new function")
                    {
                        req = "let number_3 = 15";
                        MakeRequest(nodeBuilder, req);

                        req = "fn sum = function + number_3";
                        MakeRequest(nodeBuilder, req);

                        THEN("We retrieve value of this func")
                        {
                            std::shared_ptr<Function> summFunc = manager->RetrieveFunctionByIdentificator("sum");
                            REQUIRE((std::string) *summFunc == "14");
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

        WHEN("We define function and use it in itself")
        {
            std::string req = "fn function = function - function";

            bool wasError = false;

            try
            {
                MakeRequest(nodeBuilder, req);
            }
            catch(const std::exception& e)
            {
                wasError = true;
                std::cerr << e.what() << '\n';
            }

            THEN("We have exception that function is not defined")
            {
                REQUIRE(wasError);
            }
        }
    }
}

SCENARIO("Declare and define variables in different cases and without spaces between words and symbols")
{
    GIVEN("Gentelman kit(empty resourses)")
    {
        std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
        std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

        WHEN("We declare variable in incorrect way we have error")
        {
            std::string req = "varchar";
            bool wasError = false;

            try
            {
                MakeRequest(nodeBuilder, req);
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }
            
            REQUIRE(wasError);
        }

        WHEN("We define variable without spaces between sign")
        {
            std::string req = "let number=4";
            bool wasError = false;

            try
            {
                MakeRequest(nodeBuilder, req);
            }
            catch(const std::exception& e)
            {
                wasError = true;
            }
            
            REQUIRE(!wasError);
        }

        WHEN("")
        {
            
        }
    }
}
