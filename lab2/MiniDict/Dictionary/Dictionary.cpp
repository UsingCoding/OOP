#include "./Dictionary.hpp"

Dictionary::Dictionary()
{

}

std::vector<std::string> Dictionary::retrieveTranslation(std::string key, const  Locale & locale)
{
    std::map<std::string, std::vector<std::string>> &currDictImpl =  dictEnToRu;

    if (locale == EN)
    {
        currDictImpl = dictRuToEn;
    }

    std::map<std::string, std::vector<std::string>>::iterator result = currDictImpl.find(key);

    if (result == currDictImpl.end())
    {
        throw DictionaryException("Key not found");
    }

    return result->second;
}

void Dictionary::addTranslation(std::string key, std::string value, const  Locale & locale)
{
    std::map<std::string, std::vector<std::string>> &currDictImpl =  dictEnToRu;

    if (locale == EN)
    {
        currDictImpl = dictRuToEn;
    }

    std::map<std::string, std::vector<std::string>>::iterator result = currDictImpl.find(key);

    if (result == currDictImpl.end())
    {
        currDictImpl[key] = std::vector<std::string> {value};
        return;
    }

    (result->second).push_back(value);
}
