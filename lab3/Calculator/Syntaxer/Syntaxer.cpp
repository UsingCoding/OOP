#include "./Syntaxer.hpp"
#include "../Lexer/Lexer.hpp"
#include "../../../Utils/StringUtils.hpp"
#include "../Domain/ResourceManger/ResourceManager.hpp"

#include <stdexcept>
#include <iostream>
#include "../Domain/ArithmeticObjects/Function.hpp"
#include "../Domain/ArithmeticObjects/Variable.hpp"
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

const std::string Syntaxer::FUNCTION_TERMINAL = "fn";
const std::string Syntaxer::VARAIBLE_DECLARATION_TERMINAL = "var";
const std::string Syntaxer::VARAIBLE_DEFINITION_TERMINAL = "let";

void Syntaxer::MapTokensIntoModels(const std::vector<std::string> & tokens)
{
    if (tokens[0] == FUNCTION_TERMINAL)
    {
        MapIntoFunction(tokens);
        return;
    }

    if (tokens[0] == VARAIBLE_DECLARATION_TERMINAL)
    {
        MapIntoNewVariable(tokens);
        return;
    }

    if (tokens[0] == VARAIBLE_DEFINITION_TERMINAL)
    {
        MapIntoCurrentVariable(tokens);
        return;
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

void Syntaxer::MapIntoFunction(const std::vector<std::string> & tokens)
{
    // Сверение о занятости идентификатора для функции

    // Function func;

}

void Syntaxer::MapIntoCurrentVariable(const std::vector<std::string> & tokens)
{
    // Сверение о занятости идентификатора для переменной

    if (tokens[2] != std::string (StringUtils::StringConcatenator() << Lexer::EQUALS_SIGN))
    {
        throw std::domain_error(StringUtils::StringConcatenator() << "Expected " << Lexer::EQUALS_SIGN << " got " << tokens[2]);
    }

    Variable var;

    if (tokens.size() == 4)
    {
        try
        {
            var.SetValue(std::stod(tokens[3].c_str()));
        }
        catch(const std::exception& e)
        {
            throw std::domain_error("Got error in operand");
        }
        
        return;
    }
}

void Syntaxer::MapIntoNewVariable(const std::vector<std::string> & tokens)
{
    // Сверение о занятости идентификатора для переменной

    if (tokens.size() > 2)
    {
        throw std::domain_error("Unexpected params after declaration variable");
    }
    
    Variable var;
}
