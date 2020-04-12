#include <iostream>

#include "./Dictionary.hpp"
#include <algorithm>

Dictionary::Dictionary()
{

}

std::vector<std::string> Dictionary::retrieveTranslation(std::string key, const Locale & locale)
{
    dict *currDictImplPtr;

    if (locale == RU)
    {
        currDictImplPtr = &dictEnToRu;
    }
    else
    {
        currDictImplPtr = &dictRuToEn;
    }

    std::transform(key.begin(), key.end(), key.begin(), tolower);

    std::map<std::string, std::vector<std::string>>::iterator result = (*currDictImplPtr).find(key);

    if (result == (*currDictImplPtr).end())
    {
        throw DictionaryException("Key not found");
    }

    return result->second;
}

void Dictionary::addTranslation(std::string key, std::string value, const Locale & locale)
{
    dict *currDictImplPtr;

    if (locale == RU)
    {
        currDictImplPtr = &dictEnToRu;
    }
    else
    {
        currDictImplPtr = &dictRuToEn;
    }

    std::transform(key.begin(), key.end(), key.begin(), tolower);

    std::map<std::string, std::vector<std::string>>::iterator result = (*currDictImplPtr).find(key);

    if (result == (*currDictImplPtr).end())
    {
        (*currDictImplPtr)[key] = std::vector<std::string> {value};
        return;
    }

    (result->second).push_back(value);
}
