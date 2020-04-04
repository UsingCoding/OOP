#pragma once
#include <map>
#include <vector>
#include "./Exception/DictionaryException.hpp"

class Dictionary
{
private:
    std::map<std::string, std::vector<std::string>> dictRuToEn;
    std::map<std::string, std::vector<std::string>> dictEnToRu;
public:
    Dictionary();

    enum Locale {
        RU,
        EN
    };
    std::vector<std::string> retrieveTranslation(std::string key, const Locale & locale);
    void addTranslation(std::string key, std::string value, const Locale & locale);
};
