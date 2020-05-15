#include "./ResourceManager.hpp"
#include <stdexcept>

#include <iostream>

std::shared_ptr<Variable> ResourceManager::RetrieveVariableByIdentificator(const std::string & name)
{
    auto it = variableCollection.find(name);
    if (it == variableCollection.end())
    {
        throw std::runtime_error("No variable by this identificator exist: " + name);
    }
    return it->second;
}

std::shared_ptr<Function> & ResourceManager::RetrieveFunctionByIdentificator(const std::string & name)
{
    auto it = functionCollection.find(name);
    if (it == functionCollection.end())
    {
        throw std::runtime_error("No function by this identificator exist: " + name);
    }
    
    return it->second;
}

std::shared_ptr<UnitOfArithmetic> ResourceManager::RetrieveByIdentificator(const std::string & name)
{
    try
    {
        return RetrieveVariableByIdentificator(name);
    }
    catch(const std::exception& e)
    {
        
    }
    
    try
    {
        return RetrieveFunctionByIdentificator(name);
    }
    catch(const std::exception& e)
    {
        
    }

    throw std::runtime_error("No variable or function by this identificator exist: " + name);
}

bool ResourceManager::IsIdentificatorFree(const std::string & name) const
{
    return variableCollection.find(name) == variableCollection.end() && functionCollection.find(name) == functionCollection.end();
}

void ResourceManager::Add(const std::string & identificator, std::shared_ptr<Variable> variable)
{
    variableCollection[identificator] = std::move(variable);
}

void ResourceManager::Add(const std::string & identificator, std::shared_ptr<Function> function)
{
    functionCollection[identificator] = std::move(function);
}

std::map<std::string, double> ResourceManager::GetVariablesNamesWithValues() const
{
    std::map<std::string, double> result;

    for (auto it = variableCollection.begin(); it != variableCollection.end(); it++)
    {
        result.insert(std::make_pair(it->first, *(it->second)));
    }

    return result;
}

std::map<std::string, double> ResourceManager::GetFunctionsNamesWithValues() const
{
    std::map<std::string, double> result;
    std::cout << "Request" << std::endl;

    for (auto it = functionCollection.begin(); it != functionCollection.end(); it++)
    {
        result.insert(std::make_pair(it->first, *(it->second)));
    }

    std::cout << "Print later" << std::endl;
    return result;
}