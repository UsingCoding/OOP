#include "./Interpreter.hpp"
#include "../NodeBuilder/NodeBuilderInput.hpp"
#include "../../../Utils/StringUtils.hpp"
#include "../Parser/Parser.hpp"
#include <iostream>
#include <string>

const std::string Interpreter::PRINT_IDENTIFICATOR_VALUE = "print";
const std::string Interpreter::PRINT_VARIABLES = "printvars";
const std::string Interpreter::PRINT_FUNCTIONS = "printfns";

std::string Interpreter::Handle(const std::string & query) const
{
    auto tokens = Parser::RetrieveTokensList(query);

    if (tokens.size() == 0)
    {
        return "";
    }

    if (tokens[0] == PRINT_VARIABLES)
    {
        return HandlePrintVarValuesCommand();
    }
    
    if (tokens[0] == PRINT_FUNCTIONS)
    {
        return HandlePrintFunctionsValuesCommand();
    }
    if (tokens[0] == PRINT_IDENTIFICATOR_VALUE)
    {
        return HandlePrintIdentificatorValueCommand(tokens[1]);
    }
    try
    {
        std::unique_ptr<NodeBuilderInput> input = Parser::BuildInput(tokens);
        nodeBuilder->MapIntoModels(*input);

        return "Success";
    }
    catch(const std::exception& e)
    {
        return e.what();
    }
    
}

std::string Interpreter::HandlePrintIdentificatorValueCommand(const std::string & identificator) const
{
    try
    {
        return (std::string) *(manager->RetrieveByIdentificator(identificator));
    }
    catch(const std::exception& e)
    {
        return e.what();
    }
}

std::string Interpreter::HandlePrintVarValuesCommand() const
{
    StringUtils::StringConcatenator res;
    std::map<std::string, std::string> vars = manager->GetVariablesNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        res << it->first << " = " << it->second << '\n';
    }

    return res;
}

std::string Interpreter::HandlePrintFunctionsValuesCommand() const
{
    StringUtils::StringConcatenator res;
    std::map<std::string, std::string> vars = manager->GetFunctionsNamesWithValues();
    for (auto it = vars.begin(); it != vars.end(); it++)
    {
        res << it->first << " = " << it->second << '\n';
    }

    return res;
}
