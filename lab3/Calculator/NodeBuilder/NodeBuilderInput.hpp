#pragma once

#include <string>

class NodeBuilderInput
{
public:
    enum NodeCreationType
    {
        CurrentVariable,
        NewVariable,
        Function
    };

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName, std::string firstOperandName, std::string secondOperandName, double value, double(*operation)(double, double)): 
    nodeCreationType(nodeCreationType), nodeName(nodeName), firstOperandName(firstOperandName), secondOperandName(secondOperandName), value(value), operation(operation){}

    NodeCreationType GetNodeCreationType() const;
    std::string const & GetNodeName() const;
    std::string const & GetFirstOperandName() const;
    std::string const & GetSecondOperandName() const;
    double GetValue() const;
    double(*GetOperation() const)(double, double);

private:
    NodeCreationType nodeCreationType;
    std::string nodeName;    
    std::string firstOperandName;
    std::string secondOperandName;
    double value;
    double(*operation)(double, double);
};
