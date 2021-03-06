#include "./NodeBuilder.hpp"

#include "../../../Utils/StringUtils.hpp"


#include <stdexcept>
#include <iostream>
#include "../Domain/ArithmeticObjects/Function.hpp"
#include "../Domain/ArithmeticObjects/Variable.hpp"
#include "../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"

void NodeBuilder::MapIntoModels(const std::unique_ptr<NodeBuilderInput> & input)
{
    switch (input->GetNodeCreationType())
    {
    case NodeBuilderInput::NodeCreationType::Function:
        MapIntoFunction(input);
        break;
    case NodeBuilderInput::NodeCreationType::CurrentVariable:
        MapIntoCurrentVariable(input);
        break;
    case NodeBuilderInput::NodeCreationType::NewVariable:
        MapIntoNewVariable(input);
        break;
    default:
        throw std::runtime_error("Unknown node type");
        break;
    }
}

void NodeBuilder::MapIntoFunction(const std::unique_ptr<NodeBuilderInput> & input)
{
    if (!manager->IsIdentificatorFree(input->GetNodeName()))
    {
        throw std::domain_error("Function with this identificator " + input->GetNodeName() + " already exists");
    }

    std::shared_ptr<Function> func;

    if (input->GetOperation() == nullptr)
    {
        std::shared_ptr<UnitOfArithmetic> firstArgument = manager->RetrieveByIdentificator(input->GetFirstOperandName());

        func = std::make_shared<Function>(firstArgument);
    }
    else
    {
        std::shared_ptr<UnitOfArithmetic> firstArgument = manager->RetrieveByIdentificator(input->GetFirstOperandName());
        std::shared_ptr<UnitOfArithmetic> secondArgument = manager->RetrieveByIdentificator(input->GetSecondOperandName());

        func = std::make_shared<Function>(firstArgument, secondArgument, input->GetOperation());
    }

    manager->Add(input->GetNodeName(), std::move(func));
}

void NodeBuilder::MapIntoCurrentVariable(const std::unique_ptr<NodeBuilderInput> & input)
{
    try
    {
        MapIntoNewVariable(input);
    }
    catch(const std::exception& e)
    {}

    std::shared_ptr<Variable> var = manager->RetrieveVariableByIdentificator(input->GetNodeName());

    if (manager->IsIdentificatorFree(input->GetFirstOperandName()))
    {
        var->SetValue(input->GetValue());
    }
    else
    {
        var->SetValue(*(manager->RetrieveVariableByIdentificator(input->GetFirstOperandName())));
    }

    return;
}

void NodeBuilder::MapIntoNewVariable(const std::unique_ptr<NodeBuilderInput> & input)
{
    if (!manager->IsIdentificatorFree(input->GetNodeName()))
    {
        throw std::logic_error("Identificator for this variable already exist");
    }

    manager->Add(input->GetNodeName(), std::make_shared<Variable>());
}
