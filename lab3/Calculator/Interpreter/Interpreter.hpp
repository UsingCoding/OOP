#pragma once

#include "../NodeBuilder/NodeBuilder.hpp"
#include "../Infrastructure/ResourceManger/ResourceManager.hpp"
#include <memory>
#include <iosfwd>


class Interpreter
{
private:
    std::unique_ptr<NodeBuilder> & nodeBuilder;
    std::unique_ptr<ResourceManager> & manager;

    static const std::string PRINT_IDENTIFICATOR_VALUE;
    static const std::string PRINT_VARIABLES;
    static const std::string PRINT_FUNCTIONS;

    std::string HandlePrintVarValuesCommand() const;
    std::string HandlePrintFunctionsValuesCommand() const;
    std::string HandlePrintIdentificatorValueCommand(const std::string & identificator) const;
public:
    Interpreter(std::unique_ptr<NodeBuilder> & nodeBuilder, std::unique_ptr<ResourceManager> & manager):
    nodeBuilder(nodeBuilder), manager(manager){}

    std::string Handle(const std::string & query) const;
};
