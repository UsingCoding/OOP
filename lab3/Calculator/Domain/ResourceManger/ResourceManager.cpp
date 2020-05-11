#include "./ResourceManager.hpp"
#include <stdexcept>

std::unique_ptr<Variable> ResourceManager::RetrieveVariableByIdentificator(const std::string & name) const
{
    auto it = variableCollection.find(name);
    if (it == variableCollection.end())
    {
        throw std::runtime_error("No variable by this identificator exist");
    }
    
    return std::unique_ptr<Variable>(it->second);
}

std::unique_ptr<Function> ResourceManager::RetrieveFunctionByIdentificator(const std::string & name) const
{
    auto it = functionCollection.find(name);
    if (it == functionCollection.end())
    {
        throw std::runtime_error("No variable by this identificator exist");
    }
    
    return std::unique_ptr<Function>(it->second);
}

bool ResourceManager::IsIdentificatorFree(const std::string & name) const
{
    return variableCollection.find(name) == variableCollection.end() && functionCollection.find(name) == functionCollection.end();
}

void ResourceManager::Add(const std::string & identificator, std::unique_ptr<Variable> variable)
{
    variableCollection[identificator] = variable.get();
}

void ResourceManager::Add(const std::string & identificator, std::unique_ptr<Function> function)
{
    functionCollection[identificator] = function.get();
}
