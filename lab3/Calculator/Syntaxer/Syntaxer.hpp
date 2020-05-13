#pragma once

#include "../NodeBuilder/NodeBuilderInput.hpp"
#include <string>
#include <vector>
#include <memory>

class Syntaxer
{
private:
    static const std::string FUNCTION_TERMINAL;
    static const std::string VARAIBLE_DECLARATION_TERMINAL;
    static const std::string VARAIBLE_DEFINITION_TERMINAL;
    static bool IsArithmeticOperation(const char symbol);
    static double(*RetrieveArithmeticalOperation(const char symbol))(double, double);
    static bool IsIdentificatorCorrect(const std::string & identificator);

    static void ParseVariableDeclaration(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseVariableDefinition(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    static void ParseFunctionCreation(std::unique_ptr<NodeBuilderInput> & input, const std::vector<std::string> & tokens);
    
public:
    static std::unique_ptr<NodeBuilderInput> ParseTokens(const std::vector<std::string> & tokens);
};

