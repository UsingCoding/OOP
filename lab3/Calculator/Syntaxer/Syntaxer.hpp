#pragma once

#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include <string>
#include <vector>

class Syntaxer
{
private:
    static const std::string FUNCTION_TERMINAL;
    static const std::string VARAIBLE_DECLARATION_TERMINAL;
    static const std::string VARAIBLE_DEFINITION_TERMINAL;

    static void MapIntoFunction(const std::vector<std::string> & tokens);
    static void MapIntoCurrentVariable(const std::vector<std::string> & tokens);
    static void MapIntoNewVariable(const std::vector<std::string> & tokens);
    static bool IsArithmeticOperation(const char symbol);
    static double(*RetrieveArithmeticalOperation(const char symbol))(double, double);

public:
    static void MapTokensIntoModels(const std::vector<std::string> & tokens);
};

