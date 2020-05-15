#pragma once

#include "../NodeBuilder/NodeBuilderInput.hpp"
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"
#include <string>
#include <vector>
#include <memory>

class Syntaxer
{
private:
    static const std::string FUNCTION_TERMINAL;
    static const std::string VARAIBLE_DECLARATION_TERMINAL;
    static const std::string VARAIBLE_DEFINITION_TERMINAL;

    // static double(*RetrieveArithmeticalOperation(const char symbol))(double, double);
    static ArithmeticOperaions::ArithmeticOperation RetrieveArithmeticalOperation(const char symbol);
    static bool IsIdentificatorCorrect(const std::string & identificator);

    static void ParseVariableDeclaration(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseVariableDefinition(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    
public:
    static std::unique_ptr<NodeBuilderInput> ParseTokens(const std::vector<std::string> & tokens);

    static constexpr char SPACE = ' ';
    static constexpr char EQUALS_SIGN = '=';
    static constexpr char PLUS_SIGN = '+';
    static constexpr char MINUS_SIGN = '-';
    static constexpr char MULTIPLY_SIGN = '*';
    static constexpr char DIVIDE_SIGN = '/';
};

