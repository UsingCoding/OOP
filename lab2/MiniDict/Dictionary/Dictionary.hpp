#pragma once
#include <map>
#include <vector>
#include "./Exception/DictionaryException.hpp"


class Dictionary
{
public:
    typedef std::map<std::string, std::vector<std::string>> dict;
    Dictionary();

    enum Locale {
        RU,
        EN
    };
    std::vector<std::string> RetrieveTranslation(std::string & key, const Locale & destLocale) const;
    void AddTranslation(std::string & key, std::string & value, const Locale & destLocale);


    void debug();

private:
    dict dictRuToEn;
    dict dictEnToRu;

    void WriteTranslationIntoDict(std::string & key, const std::string & value, dict & dictionary);
    std::vector<std::string> RetrieveTranslationFromDict(const std::string & key, const dict & dictionary) const;
};
