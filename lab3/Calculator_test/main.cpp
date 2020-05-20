#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>
#include <memory>
#include <sstream>

#include "../Calculator/NodeBuilder/NodeBuilder.hpp"
#include "../Calculator/Parser/Parser.hpp"
#include "../Calculator/Domain/ResourceManger/ResourceManager.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Variable.hpp"
#include "../Calculator/Domain/ArithmeticObjects/Function.hpp"


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

                        
                    }

                }
            }
        }
    }
}
