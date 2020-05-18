#include "./Syntaxer.hpp"
#include "../Lexer/Lexer.hpp"
#include "../../../Utils/StringUtils.hpp"


#include <stdexcept>
#include <iostream>
#include <regex>
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

const std::string Syntaxer::FUNCTION_TERMINAL = "fn";
const std::string Syntaxer::VARAIBLE_DECLARATION_TERMINAL = "var";
const std::string Syntaxer::VARAIBLE_DEFINITION_TERMINAL = "let";

std::unique_ptr<NodeBuilderInput> Syntaxer::ParseTokens(const std::vector<std::string> & tokens)
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

ArithmeticOperaions::ArithmeticOperation Syntaxer::RetrieveArithmeticalOperation(const char symbol)
{
    switch (symbol)
    {
    case Syntaxer::PLUS_SIGN:
        return ArithmeticOperaions::Add;
    case Syntaxer::MINUS_SIGN:
        return ArithmeticOperaions::Subtraction;
    case Syntaxer::MULTIPLY_SIGN:
        return ArithmeticOperaions::Multiply;
    case Syntaxer::DIVIDE_SIGN:
        return ArithmeticOperaions::Divide;    
    default:
        throw std::domain_error(StringUtils::StringConcatenator() << "Unknown arithmetic operarion " << symbol);
        break;
    }
}

bool Syntaxer::IsIdentificatorCorrect(const std::string & identificator)
{
    std::regex regular("([a-zA-Z])([a-zA-Z_\\d]*)$");
    return std::regex_match(identificator, regular);
}

void Syntaxer::ParseVariableDeclaration(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
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

void Syntaxer::ParseVariableDefinition(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
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

void Syntaxer::ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
{
    if (tokens.size() > 6)
    {
        throw std::domain_error("Unknown params after declaration function");
    }

    if (tokens.size() < 6)
    {
        throw std::domain_error("No enough params to declare function");
    }

    if (!IsIdentificatorCorrect(tokens[1]) || !IsIdentificatorCorrect(tokens[3]) || !IsIdentificatorCorrect(tokens[5]))
    {
        throw std::logic_error("Incorrect name of identifier");
    }

    if (tokens[4].size() > 1)
    {
        throw std::domain_error("Incorrect arithmetic operation " + tokens[4]);
    }
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::Function, tokens[1], tokens[3], tokens[5], RetrieveArithmeticalOperation(tokens[4][0])); 
}
