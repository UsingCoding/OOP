#include "Parser.hpp"

#include <iostream>
#include "../../../Utils/StringUtils.hpp"

#include <stdexcept>
#include <iostream>
#include <regex>

const std::string Parser::FUNCTION_TERMINAL = "fn";
const std::string Parser::VARAIBLE_DECLARATION_TERMINAL = "var";
const std::string Parser::VARAIBLE_DEFINITION_TERMINAL = "let";


bool Parser::IsTerminalDivider(const char symbol)
{
    switch (symbol)
    {
    case Parser::SPACE:
    case Parser::EQUALS_SIGN:
    case Parser::PLUS_SIGN:
    case Parser::MINUS_SIGN:
    case Parser::MULTIPLY_SIGN:
    case Parser::DIVIDE_SIGN:
        return true;
    default:
        return false;
    }
}

std::vector<std::string> Parser::RetrieveTokensList(const std::string & value)
{
    std::vector<std::string> result;
    int offset = -1;

    for (size_t i = 0; i < value.length(); i++)
    {
        if (!IsTerminalDivider(value[i]))
        {
            offset = offset == -1 ? 1 : offset + 1;
            continue;
        }
        if (offset != -1)
        {
            result.push_back(value.substr(i - offset, offset));
        }
        
        if (value[i] != Parser::SPACE)
        {
            result.push_back(StringUtils::StringConcatenator() << value[i]);
        }
        
        offset = -1;
    }
    if (offset != -1)
    {
        result.push_back(value.substr(value.length() - offset, offset));
    }

    return result;
}

std::unique_ptr<NodeBuilderInput> Parser::BuildInput(const std::vector<std::string> & tokens)
{
    std::unique_ptr<NodeBuilderInput> input;

    if (tokens[0] == FUNCTION_TERMINAL)
    {
        ParseFunctionCreation(input, tokens);
        return std::move(input);
    }

    if (tokens[0] == VARAIBLE_DECLARATION_TERMINAL)
    {
        
        ParseVariableDeclaration(input, tokens);
        return std::move(input);
    }

    if (tokens[0] == VARAIBLE_DEFINITION_TERMINAL)
    {
        ParseVariableDefinition(input, tokens);
        return std::move(input);
    }
    
    throw std::domain_error("Unknown terminal " + tokens[0]);
}

ArithmeticOperaions::ArithmeticOperation Parser::RetrieveArithmeticalOperation(const char symbol)
{
    switch (symbol)
    {
    case Parser::PLUS_SIGN:
        return ArithmeticOperaions::Add;
    case Parser::MINUS_SIGN:
        return ArithmeticOperaions::Subtraction;
    case Parser::MULTIPLY_SIGN:
        return ArithmeticOperaions::Multiply;
    case Parser::DIVIDE_SIGN:
        return ArithmeticOperaions::Divide;    
    default:
        throw std::domain_error(StringUtils::StringConcatenator() << "Unknown arithmetic operarion " << symbol);
        break;
    }
}

bool Parser::IsIdentificatorCorrect(const std::string & identificator)
{
    std::regex regular("([a-zA-Z])([a-zA-Z_\\d]*)$");
    return std::regex_match(identificator, regular);
}

void Parser::ParseVariableDeclaration(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
{
    if (tokens.size() > 2)
    {
        throw std::domain_error("Unknown params after declaration variable");
    }

    if (tokens.size() < 2)
    {
        throw std::domain_error("Missing variable identificator");
    }
    
    if (!IsIdentificatorCorrect(tokens[1]))
    {
        throw std::domain_error("Incorrect name for identificator");
    }
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::NewVariable, tokens[1]);
}

void Parser::ParseVariableDefinition(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
{
    if (tokens.size() > 4)
    {
        throw std::domain_error("Unknown params after definition variable");
    }

    if (tokens.size() < 4)
    {
        throw std::domain_error("No enough params to define or declare variable");
    }

    double value;
    std::string firstOperandName;

    try
    {
        value = std::stod(tokens[3].c_str());
    }
    catch(const std::exception& e)
    {
        firstOperandName = tokens[3];
    }
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::CurrentVariable, tokens[1], firstOperandName, value);
}

void Parser::ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
{
    if (tokens.size() > 6)
    {
        throw std::domain_error("Unknown params after declaration function");
    }

    if (tokens.size() < 6)
    {
        throw std::domain_error("No enough params to declare function");
    }

    if (!IsIdentificatorCorrect(tokens[1]) || !IsIdentificatorCorrect(tokens[3]))
    {
        throw std::logic_error("Incorrect name of identifier");
    }

    if (tokens.size() > 4)
    {
            
    }
    

    if (!IsIdentificatorCorrect(tokens[1]) || !IsIdentificatorCorrect(tokens[3]))
    {
        throw std::logic_error("Incorrect name of identifier");
    }

    if (tokens[4].size() > 1)
    {
        throw std::domain_error("Incorrect arithmetic operation " + tokens[4]);
    }
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::Function, tokens[1], tokens[3], tokens[5], RetrieveArithmeticalOperation(tokens[4][0])); 
}
