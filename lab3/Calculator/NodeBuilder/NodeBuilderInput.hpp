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

    NodeBuilderInput(NodeCreationType nodeCreationType, std::string nodeName, std::string firstOperandName, std::string secondOperandName, double value): 
    nodeCreationType(nodeCreationType), nodeName(nodeName), firstOperandName(firstOperandName), secondOperandName(secondOperandName), value(value){}

    NodeCreationType getNodeCreationType() const;
    std::string const & getNodeName() const;
    std::string const & getFirstOperandName() const;
    std::string const & getSecondOperandName() const;
    double GetValue() const;

    // void setNodeCreationType(NodeCreationType );
    // void setNodeName(std::string );
    // void setFirstOperandName(std::string );
    // void setSecondOperandName(std::string );

private:
    NodeCreationType nodeCreationType;
    std::string nodeName;    
    std::string firstOperandName;
    std::string secondOperandName;
    double value;
};
