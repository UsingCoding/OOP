#include <iostream>

#include "./Dictionary.hpp"
#include <algorithm>

Dictionary::Dictionary()
{

}

std::vector<std::string> Dictionary::retrieveTranslation(std::string & key, const Locale & locale)
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

void Dictionary::addTranslation(std::string & key, std::string & value, const Locale & destLocale)
{
    if (destLocale == RU)
    {
        WriteTranslationIntoDict(key, value, dictEnToRu);
        WriteTranslationIntoDict(value, key, dictRuToEn);
    }
    else
    {
        WriteTranslationIntoDict(key, value, dictRuToEn);
        WriteTranslationIntoDict(value, key, dictEnToRu);
    }
}

void Dictionary::WriteTranslationIntoDict(std::string & key, const std::string & value, dict & dictionary)
{
    std::transform(key.begin(), key.end(), key.begin(), tolower);

    std::map<std::string, std::vector<std::string>>::iterator result = dictionary.find(key);

    if (result == dictionary.end())
    {
        dictionary[key] = std::vector<std::string> {value};
        return;
    }

    (result->second).push_back(value);
}


void Dictionary::debug()
{
    dict::iterator it;

    it = dictEnToRu.begin();

    for (int i = 0; it != dictEnToRu.end(); it++, i++)
    {
        std::cout << "Key - " << it->first << ", value..." << std::endl;
        for (size_t i = 0; i < it->second.size(); i++)
        {
            std::cout << it->second[i] << std::endl;
        }
        std::cout << std::endl;
    }

    it = dictRuToEn.begin();

    for (int i = 0; it != dictRuToEn.end(); it++, i++)
    {
        std::cout << "Key - " << it->first << ", value..." << std::endl;
        for (size_t i = 0; i < it->second.size(); i++)
        {
            std::cout << it->second[i] << std::endl;
        }
        std::cout << std::endl;
    }
}
