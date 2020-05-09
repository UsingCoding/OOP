#include <iostream>

#include "./Dictionary.hpp"
#include <algorithm>

const std::string Dictionary::RU_LOCALE = "RU";
const std::string Dictionary::EN_LOCALE = "EN";

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

Dictionary::Locale Dictionary::RetrieveLocaleFromString(const std::string & locale)
{
    if (locale == RU_LOCALE)
    {
        return Dictionary::Locale::RU;
    }
    
    if (locale == EN_LOCALE)
    {
        return Dictionary::Locale::EN;
    }

    throw std::logic_error("Неизвестная локаль");
}
