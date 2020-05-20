#pragma once

#include <map>
#include <string>
#include "../../Domain/ArithmeticObjects/UnitOfArithmetic.hpp"
#include "../../Domain/ArithmeticObjects/Function.hpp"
#include "../../Domain/ArithmeticObjects/Variable.hpp"
#include <memory>

class ResourceManager
{
private:
    std::map<std::string, std::shared_ptr<Variable>> variableCollection;
    std::map<std::string, std::shared_ptr<Function>> functionCollection;

public:
    std::shared_ptr<Variable>  RetrieveVariableByIdentificator(const std::string & name);
    std::shared_ptr<Function> & RetrieveFunctionByIdentificator(const std::string & name);
    std::shared_ptr<UnitOfArithmetic> RetrieveByIdentificator(const std::string & name);
    bool IsIdentificatorFree(const std::string & name) const;
    void Add(const std::string & identificator, std::shared_ptr<Variable> unitOfArithmetic);
    void Add(const std::string & identificator, std::shared_ptr<Function> unitOfArithmetic);

    std::map<std::string, std::string> GetVariablesNamesWithValues() const;
    std::map<std::string, std::string> GetFunctionsNamesWithValues() const;
};