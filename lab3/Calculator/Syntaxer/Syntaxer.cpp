#include "./Syntaxer.hpp"
#include "../Lexer/Lexer.hpp"
#include "../../../Utils/StringUtils.hpp"


#include <stdexcept>
#include <iostream>
#include "../Domain/ArithmeticObjects/Function.hpp"
#include "../Domain/ArithmeticObjects/Variable.hpp"
#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

const std::string Syntaxer::FUNCTION_TERMINAL = "fn";
const std::string Syntaxer::VARAIBLE_DECLARATION_TERMINAL = "var";
const std::string Syntaxer::VARAIBLE_DEFINITION_TERMINAL = "let";

void Syntaxer::MapTokensIntoModels(const std::vector<std::string> & tokens)
{
    // if (tokens[2] != std::string (StringUtils::StringConcatenator() << Lexer::EQUALS_SIGN))
    // {
    //     throw std::domain_error(StringUtils::StringConcatenator() << "Expected " << Lexer::EQUALS_SIGN << " got " << tokens[2]);
    // }

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
    if (tokens.size() != 6)
    {
        throw std::domain_error("Incorrect parameters to declare function");
    }
    
    if (!manager->IsIdentificatorFree(tokens[1]))
    {
        throw std::logic_error("Identificator for this function already exist");
    }

    std::unique_ptr<UnitOfArithmetic> firstArgument;
    std::unique_ptr<UnitOfArithmetic> secondArgument;

    firstArgument = manager->RetrieveByIdentificator(tokens[3]);
    secondArgument = manager->RetrieveByIdentificator(tokens[5]);

    double(*operation)(double, double) = RetrieveArithmeticalOperation(tokens[4][0]);

    std::unique_ptr<Function> func = std::make_unique<Function>(firstArgument, secondArgument);

    func->SetOperation(operation);
}

void Syntaxer::MapIntoCurrentVariable(const std::vector<std::string> & tokens)
{
    if (tokens.size() != 4)
    {
        throw std::logic_error("Incorrect params to difine variable");
    }

    MapIntoNewVariable(tokens);

    std::unique_ptr<Variable> & var = manager->RetrieveVariableByIdentificator(tokens[1]);
    
    if (manager->IsIdentificatorFree(tokens[3]))
    {
        var->SetValue(std::stod(tokens[3].c_str()));
    }
    else
    {
        var->SetValue(*(manager->RetrieveVariableByIdentificator(tokens[3])));
    }
    
    return;
}

void Syntaxer::MapIntoNewVariable(const std::vector<std::string> & tokens)
{
    if (!manager->IsIdentificatorFree(tokens[1]))
    {
        throw std::logic_error("Identificator for this variable already exist");
    }
    
    manager->Add(tokens[1], std::make_unique<Variable>());
}
