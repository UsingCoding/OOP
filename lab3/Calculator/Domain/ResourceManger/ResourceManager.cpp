#include "./ResourceManager.hpp"
#include <stdexcept>

#include <iostream>

std::unique_ptr<Variable> & ResourceManager::RetrieveVariableByIdentificator(const std::string & name)
{
    auto it = variableCollection.find(name);
    if (it == variableCollection.end())
    {
        throw std::runtime_error("No variable by this identificator exist: " + name);
    }
    std::cout << "qweqw" << std::endl;
    return it->second;
}

std::unique_ptr<Function> & ResourceManager::RetrieveFunctionByIdentificator(const std::string & name)
{
    auto it = functionCollection.find(name);
    if (it == functionCollection.end())
    {
        throw std::runtime_error("No function by this identificator exist: " + name);
    }
    
    return it->second;
}

std::unique_ptr<UnitOfArithmetic> & ResourceManager::RetrieveByIdentificator(const std::string & name)
{
    // try
    // {
    //     return RetrieveVariableByIdentificator(name);
    // }
    // catch(const std::exception& e)
    // {
        
    // }
    
    // try
    // {
    //     return RetrieveFunctionByIdentificator(name);
    // }
    // catch(const std::exception& e)
    // {
        
    // }

    throw std::runtime_error("No variable or function by this identificator exist: " + name);
}

bool ResourceManager::IsIdentificatorFree(const std::string & name) const
{
    return variableCollection.find(name) == variableCollection.end() && functionCollection.find(name) == functionCollection.end();
}

void ResourceManager::Add(const std::string & identificator, std::unique_ptr<Variable> variable)
{
    variableCollection[identificator] = std::move(variable);
}

void ResourceManager::Add(const std::string & identificator, std::unique_ptr<Function> function)
{
    functionCollection[identificator] = std::move(function);
}