#include <iostream>
#include "./Lexer/Lexer.hpp"
#include "./Syntaxer/Syntaxer.hpp"
#include "./NodeBuilder/NodeBuilder.hpp"
#include "./NodeBuilder/NodeBuilderInput.hpp"
#include <vector>
#include <memory>
#include "./Domain/ResourceManger/ResourceManager.hpp"

#include "../../Utils/StringUtils.hpp"
#include "./Domain/ArithmeticOperations/ArithmeticOperations.hpp"

const std::string PRINT_IDENTIFICATOR_VALUE = "print";
const std::string PRINT_VARIABLES = "printvars";
const std::string PRINT_FUNCTIONS = "printfns";

void HandlePrintIdentificatorValueCommand(const std::string & identificator, std::unique_ptr<ResourceManager> & manager);

void HandlePrintVarValuesCommand(std::unique_ptr<ResourceManager> & manager);

void HandlePrintFunctionsValuesCommand(std::unique_ptr<ResourceManager> & manager);


int main(int argc, char const *argv[])
{
    std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
    std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

    std::string userIn;
    std::vector<std::string> res;
    std::unique_ptr<NodeBuilderInput> input;

    while (getline(std::cin, userIn))
    {
        if (userIn == PRINT_VARIABLES)
        {
            HandlePrintVarValuesCommand(manager);
            continue;
        }
        
        if (userIn == PRINT_FUNCTIONS)
        {
            HandlePrintFunctionsValuesCommand(manager);
            continue;
        }

        res = Lexer::RetrieveTokensList(userIn);

        if (res[0] == PRINT_IDENTIFICATOR_VALUE)
        {
            HandlePrintIdentificatorValueCommand(res[1], manager);
            continue;
        }

        try
        {
            input = Syntaxer::ParseTokens(res);
            nodeBuilder->MapIntoModels(*input);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }              
    }
   
    return 0;
}

void HandlePrintIdentificatorValueCommand(const std::string & identificator, std::unique_ptr<ResourceManager> & manager)
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

void HandlePrintVarValuesCommand(std::unique_ptr<ResourceManager> & manager)
{
    std::map<std::string, std::string> vars = manager->GetVariablesNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

void HandlePrintFunctionsValuesCommand(std::unique_ptr<ResourceManager> & manager)
{
    std::map<std::string, std::string> vars = manager->GetFunctionsNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}
