#pragma once

#include <string>
#include "../Domain/ArithmeticOperations/ArithmeticOperations.hpp"

class NodeBuilderInput
{
public:
    enum NodeCreationType
    {
        CurrentVariable,
        NewVariable,
        Function
    };

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName):
    nodeCreationType(nodeCreationType), nodeName(nodeName) {}

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName, std::string firstOperandName, double value):
    nodeCreationType(nodeCreationType), nodeName(nodeName), firstOperandName(firstOperandName), value(value) {}

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName, std::string firstOperandName, std::string secondOperandName, ArithmeticOperaions::ArithmeticOperation operation):
    nodeCreationType(nodeCreationType), nodeName(nodeName), firstOperandName(firstOperandName), secondOperandName(secondOperandName), operation(operation){}

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName, std::string firstOperandName):
    nodeCreationType(nodeCreationType), nodeName(nodeName), firstOperandName(firstOperandName), operation(nullptr) {}

    NodeCreationType GetNodeCreationType() const;
    std::string const & GetNodeName() const;
    std::string const & GetFirstOperandName() const;
    std::string const & GetSecondOperandName() const;
    double GetValue() const;
    ArithmeticOperaions::ArithmeticOperation GetOperation() const;

private:
    NodeCreationType nodeCreationType;
    std::string nodeName;
    std::string firstOperandName;
    std::string secondOperandName;
    double value;
    ArithmeticOperaions::ArithmeticOperation operation;
};
