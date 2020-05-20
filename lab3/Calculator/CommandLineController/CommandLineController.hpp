#pragma once

#include "../NodeBuilder/NodeBuilder.hpp"
#include "../Domain/ResourceManger/ResourceManager.hpp"
#include <memory>
#include <iosfwd>


class CommandLineController
{
private:
    std::unique_ptr<NodeBuilder> & nodeBuilder;
    std::unique_ptr<ResourceManager> & manager;

    static const std::string PRINT_IDENTIFICATOR_VALUE;
    static const std::string PRINT_VARIABLES;
    static const std::string PRINT_FUNCTIONS;

    void HandlePrintVarValuesCommand() const;
    void HandlePrintFunctionsValuesCommand() const;
    void HandlePrintIdentificatorValueCommand(const std::string & identificator) const;
public:
    CommandLineController(std::unique_ptr<NodeBuilder> & nodeBuilder, std::unique_ptr<ResourceManager> & manager): 
    nodeBuilder(nodeBuilder), manager(manager){}
    void Start(std::istream & input) const;
};
