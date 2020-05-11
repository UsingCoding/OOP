#pragma once

#include <map>
#include <string>
#include "../ArithmeticObjects/Function.hpp"
#include "../ArithmeticObjects/Variable.hpp"
#include <memory>

class ResourceManager
{
private:
    std::map<std::string, Variable*> variableCollection;
    std::map<std::string, Function*> functionCollection;

public:
    std::unique_ptr<Variable> RetrieveVariableByIdentificator(const std::string & name) const;
    std::unique_ptr<Function> RetrieveFunctionByIdentificator(const std::string & name) const;
    bool IsIdentificatorFree(const std::string & name) const;
    void Add(const std::string & identificator, std::unique_ptr<Variable> unitOfArithmetic);
    void Add(const std::string & identificator, std::unique_ptr<Function> unitOfArithmetic);
};