#pragma once

#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../Infrastructure/ResourceManger/ResourceManager.hpp"
#include "./NodeBuilderInput.hpp"
#include <string>
#include <vector>
#include <memory>

class NodeBuilder
{
private:
    void MapIntoFunction(const NodeBuilderInput & input);
    void MapIntoCurrentVariable(const NodeBuilderInput & input);
    void MapIntoNewVariable(const NodeBuilderInput & input);
    
    std::unique_ptr<ResourceManager> & manager;
public:
    void MapIntoModels(const NodeBuilderInput & input);
    NodeBuilder(std::unique_ptr<ResourceManager> & manager): manager(manager){}
};
