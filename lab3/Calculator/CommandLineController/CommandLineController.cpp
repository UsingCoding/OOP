#include "./CommandLineController.hpp"
#include "../NodeBuilder/NodeBuilderInput.hpp"
#include "../Parser/Parser.hpp"
#include <iostream>
#include <string>

const std::string CommandLineController::PRINT_IDENTIFICATOR_VALUE = "print";
const std::string CommandLineController::PRINT_VARIABLES = "printvars";
const std::string CommandLineController::PRINT_FUNCTIONS = "printfns";

void CommandLineController::Start(std::istream & input) const
{
    std::string userIn;
    std::unique_ptr<NodeBuilderInput> builderInput;
    while (getline(input, userIn))
    {
        auto tokens = Parser::RetrieveTokensList(userIn);

        if (tokens[0] == PRINT_VARIABLES)
        {
            HandlePrintVarValuesCommand();
            continue;
        }
        
        if (tokens[0] == PRINT_FUNCTIONS)
        {
            HandlePrintFunctionsValuesCommand();
            continue;
        }

        if (tokens[0] == PRINT_IDENTIFICATOR_VALUE)
        {
            HandlePrintIdentificatorValueCommand(tokens[1]);
            continue;
        }

        try
        {
            builderInput = Parser::BuildInput(tokens);
            nodeBuilder->MapIntoModels(*builderInput);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
}

void CommandLineController::HandlePrintIdentificatorValueCommand(const std::string & identificator) const
{
    try
    {
        std::cout << (std::string) *(manager->RetrieveByIdentificator(identificator)) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void CommandLineController::HandlePrintVarValuesCommand() const
{
    std::map<std::string, std::string> vars = manager->GetVariablesNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

void CommandLineController::HandlePrintFunctionsValuesCommand() const
{
    std::map<std::string, std::string> vars = manager->GetFunctionsNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}
