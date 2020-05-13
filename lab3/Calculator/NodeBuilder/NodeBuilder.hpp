#pragma once

#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../Domain/ResourceManger/ResourceManager.hpp"
#include "./NodeBuilderInput.hpp"
#include <string>
#include <vector>
#include <memory>

class NodeBuilder
{
private:
    void MapIntoFunction(const std::vector<std::string> & tokens);
    void MapIntoCurrentVariable(const std::vector<std::string> & tokens);
    void MapIntoNewVariable(const std::vector<std::string> & tokens);
    static bool IsArithmeticOperation(const char symbol);
    static double(*RetrieveArithmeticalOperation(const char symbol))(double, double);
    
    std::unique_ptr<ResourceManager> & manager;
public:
    void MapIntoModels(const NodeBuilderInput & input);
    NodeBuilder(std::unique_ptr<ResourceManager> & manager): manager(manager){}
};
