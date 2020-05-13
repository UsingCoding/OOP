#include "./NodeBuilder.hpp"

#include "../Syntaxer/Syntaxer.hpp"
#include "../Lexer/Lexer.hpp"
#include "../../../Utils/StringUtils.hpp"


#include <stdexcept>
#include <iostream>
#include "../Domain/ArithmeticObjects/Function.hpp"
#include "../Domain/ArithmeticObjects/Variable.hpp"
#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

void NodeBuilder::MapIntoModels(const NodeBuilderInput & input)
{
    switch (input.getNodeCreationType())
    {
    case NodeBuilderInput::NodeCreationType::Function:
        break;
    case NodeBuilderInput::NodeCreationType::CurrentVariable:
        std::cout << input.getNodeName() << std::endl;
        std::cout << input.getFirstOperandName() << std::endl;
        std::cout << input.GetValue() << std::endl;
        break;
    case NodeBuilderInput::NodeCreationType::NewVariable:
        break;
    default:
        break;
    }
}

bool NodeBuilder::IsArithmeticOperation(const char symbol)
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

double(*NodeBuilder::RetrieveArithmeticalOperation(const char symbol))(double, double)
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

void NodeBuilder::MapIntoFunction(const std::vector<std::string> & tokens)
{
    if (tokens.size() != 6)
    {
        throw std::domain_error("Incorrect parameters to declare function");
    }
    
    if (!manager->IsIdentificatorFree(tokens[1]))
    {
        throw std::logic_error("Identificator for this function already exist");
    }

    // std::unique_ptr<UnitOfArithmetic> firstArgument;
    // std::unique_ptr<UnitOfArithmetic> secondArgument;

    // firstArgument = manager->RetrieveByIdentificator(tokens[3]);
    // secondArgument = manager->RetrieveByIdentificator(tokens[5]);

    // double(*operation)(double, double) = RetrieveArithmeticalOperation(tokens[4][0]);

    // std::unique_ptr<Function> func = std::make_unique<Function>(firstArgument, secondArgument);

    // func->SetOperation(operation);
}

void NodeBuilder::MapIntoCurrentVariable(const std::vector<std::string> & tokens)
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

void NodeBuilder::MapIntoNewVariable(const std::vector<std::string> & tokens)
{
    if (!manager->IsIdentificatorFree(tokens[1]))
    {
        throw std::logic_error("Identificator for this variable already exist");
    }
    
    manager->Add(tokens[1], std::make_unique<Variable>());
}
