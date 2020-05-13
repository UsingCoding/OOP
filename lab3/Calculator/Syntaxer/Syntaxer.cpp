#include "./Syntaxer.hpp"
#include "../Lexer/Lexer.hpp"
#include "../../../Utils/StringUtils.hpp"


#include <stdexcept>
#include <iostream>
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

const std::string Syntaxer::FUNCTION_TERMINAL = "fn";
const std::string Syntaxer::VARAIBLE_DECLARATION_TERMINAL = "var";
const std::string Syntaxer::VARAIBLE_DEFINITION_TERMINAL = "let";

std::unique_ptr<NodeBuilderInput> Syntaxer::ParseTokens(const std::vector<std::string> & tokens)
{
    std::unique_ptr<NodeBuilderInput> input;

    if (tokens[0] == FUNCTION_TERMINAL)
    {
        // ParseVariableDeclaration(input, tokens);
        // return std::move(input);
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

bool Syntaxer::IsArithmeticOperation(const char symbol)
{
    switch (symbol)
    {
    case Lexer::PLUS_SIGN:
    case Lexer::MINUS_SIGN:
    case Lexer::MULTIPLY_SIGN:
    case Lexer::DIVIDE_SIGN:
        return true;
    default:
        return false;
    }
}

double(*Syntaxer::RetrieveArithmeticalOperation(const char symbol))(double, double)
{
    switch (symbol)
    {
    case Lexer::PLUS_SIGN:
        return ArithmeticOperaions::Add;
    case Lexer::MINUS_SIGN:
        return ArithmeticOperaions::Subtraction;
    case Lexer::MULTIPLY_SIGN:
        return ArithmeticOperaions::Multiply;
    case Lexer::DIVIDE_SIGN:
        return ArithmeticOperaions::Divide;    
    default:
        throw std::domain_error("Unknown arithmetic operarion");
        break;
    }
}

bool Syntaxer::IsIdentificatorCorrect(const std::string & identificator)
{
    return true;
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
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::NewVariable, tokens[1], "", "", 0);
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
    
    input = std::make_unique<NodeBuilderInput>(NodeBuilderInput::NodeCreationType::CurrentVariable, tokens[1], firstOperandName, "", value);
}

void Syntaxer::ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens)
{

}
