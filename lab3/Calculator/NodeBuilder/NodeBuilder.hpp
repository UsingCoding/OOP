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
    void MapIntoFunction(const std::unique_ptr<NodeBuilderInput> & input);
    void MapIntoCurrentVariable(const std::unique_ptr<NodeBuilderInput> & input);
    void MapIntoNewVariable(const std::unique_ptr<NodeBuilderInput> & input);

    std::unique_ptr<ResourceManager> & manager;
public:
    void MapIntoModels(const std::unique_ptr<NodeBuilderInput> & input);
    NodeBuilder(std::unique_ptr<ResourceManager> & manager): manager(manager){}
};
