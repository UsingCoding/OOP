#include "NodeBuilderInput.hpp"

NodeBuilderInput::NodeCreationType NodeBuilderInput::getNodeCreationType() const
{
    return nodeCreationType;
}

std::string const & NodeBuilderInput::getNodeName() const
{
    return nodeName;
}

std::string const & NodeBuilderInput::getFirstOperandName() const
{
    return firstOperandName;
}

std::string const & NodeBuilderInput::getSecondOperandName() const
{
    return secondOperandName;
}

double NodeBuilderInput::GetValue() const
{
    return value;
}
