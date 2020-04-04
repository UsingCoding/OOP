#include "./Dictionary.hpp"
#include <algorithm>

Dictionary::Dictionary()
{

}

std::vector<std::string> Dictionary::retrieveTranslation(std::string key, const Locale & locale)
{
    std::map<std::string, std::vector<std::string>> &currDictImpl =  dictEnToRu;

    if (locale == EN)
    {
        currDictImpl = dictRuToEn;
    }

    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); });

    std::map<std::string, std::vector<std::string>>::iterator result = currDictImpl.find(key);

    if (result == currDictImpl.end())
    {
        throw DictionaryException("Key not found");
    }

    return result->second;
}

void Dictionary::addTranslation(std::string key, std::string value, const Locale & locale)
{
    std::map<std::string, std::vector<std::string>> &currDictImpl =  dictEnToRu;

    if (locale == EN)
    {
        currDictImpl = dictRuToEn;
    }

    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); });

    std::map<std::string, std::vector<std::string>>::iterator result = currDictImpl.find(key);

    if (result == currDictImpl.end())
    {
        currDictImpl[key] = std::vector<std::string> {value};
        return;
    }

    (result->second).push_back(value);
}
