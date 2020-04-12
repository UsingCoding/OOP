#pragma once
#include <map>
#include <vector>
#include "./Exception/DictionaryException.hpp"

typedef std::map<std::string, std::vector<std::string>> dict;

class Dictionary
{
private:
    dict dictRuToEn;
    dict dictEnToRu;
public:
    Dictionary();

    enum Locale {
        RU,
        EN
    };
    std::vector<std::string> retrieveTranslation(std::string key, const Locale & locale);
    void addTranslation(std::string key, std::string value, const Locale & locale);
};
