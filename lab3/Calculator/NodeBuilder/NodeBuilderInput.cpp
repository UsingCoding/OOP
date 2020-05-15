#include "NodeBuilderInput.hpp"

NodeBuilderInput::NodeCreationType NodeBuilderInput::GetNodeCreationType() const
{
    return nodeCreationType;
}

std::string const & NodeBuilderInput::GetNodeName() const
{
    return nodeName;
}

std::string const & NodeBuilderInput::GetFirstOperandName() const
{
    return firstOperandName;
}

std::string const & NodeBuilderInput::GetSecondOperandName() const
{
    return secondOperandName;
}

double NodeBuilderInput::GetValue() const
{
    return value;
}

ArithmeticOperaions::ArithmeticOperation NodeBuilderInput::GetOperation() const
{
    return operation;
}
