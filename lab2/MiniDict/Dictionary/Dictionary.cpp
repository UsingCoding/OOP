#include <iostream>

#include "./Dictionary.hpp"
#include <algorithm>

Dictionary::Dictionary()
{

}

std::vector<std::string> Dictionary::RetrieveTranslation(std::string & key, const Locale & locale) const
{
    std::transform(key.begin(), key.end(), key.begin(), tolower);

    if (locale == RU)
    {
        return RetrieveTranslationFromDict(key, dictEnToRu);
    }
    else
    {
        return RetrieveTranslationFromDict(key, dictRuToEn);
    }

}

std::vector<std::string> Dictionary::RetrieveTranslationFromDict(const std::string & key, const dict & dictionary) const
{
    dict::const_iterator result = dictionary.find(key);

    if (result == dictionary.end())
    {
        return std::vector<std::string>{};
    }

    return result->second;
}

void Dictionary::AddTranslation(std::string & key, std::string & value, const Locale & destLocale)
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

    dict::iterator result = dictionary.find(key);

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
