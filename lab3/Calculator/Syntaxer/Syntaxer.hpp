#pragma once

#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../Domain/ResourceManger/ResourceManager.hpp"
#include <string>
#include <vector>
#include <memory>

class Syntaxer
{
private:
    static const std::string FUNCTION_TERMINAL;
    static const std::string VARAIBLE_DECLARATION_TERMINAL;
    static const std::string VARAIBLE_DEFINITION_TERMINAL;

    void MapIntoFunction(const std::vector<std::string> & tokens);
    void MapIntoCurrentVariable(const std::vector<std::string> & tokens);
    void MapIntoNewVariable(const std::vector<std::string> & tokens);
    static bool IsArithmeticOperation(const char symbol);
    static double(*RetrieveArithmeticalOperation(const char symbol))(double, double);
    
    std::unique_ptr<ResourceManager> & manager;
public:
    void MapTokensIntoModels(const std::vector<std::string> & tokens);

    Syntaxer(std::unique_ptr<ResourceManager> & manager): manager(manager){}
};

