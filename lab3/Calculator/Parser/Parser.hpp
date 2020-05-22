#pragma once

#include "../NodeBuilder/NodeBuilderInput.hpp"
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iosfwd>

class Parser
{
private:
    static bool IsTerminalDivider(const char symbol);

    static const std::string FUNCTION_TERMINAL;
    static const std::string VARAIBLE_DECLARATION_TERMINAL;
    static const std::string VARAIBLE_DEFINITION_TERMINAL;

    static ArithmeticOperaions::ArithmeticOperation RetrieveArithmeticalOperation(const char symbol);
    static bool IsIdentificatorCorrect(const std::string & identificator);

    static void ParseVariableDeclaration(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseVariableDefinition(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);

    static void ParseSignleOperandCreationFunction(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseTwoOperandsCreationFunction(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);

    static constexpr char SPACE = ' ';
    static constexpr char EQUALS_SIGN = '=';
    static constexpr char PLUS_SIGN = '+';
    static constexpr char MINUS_SIGN = '-';
    static constexpr char MULTIPLY_SIGN = '*';
    static constexpr char DIVIDE_SIGN = '/';

public:
    static std::vector<std::string> RetrieveTokensList(const std::string & value);

    static std::unique_ptr<NodeBuilderInput> BuildInput(const std::vector<std::string> & tokens);
};
