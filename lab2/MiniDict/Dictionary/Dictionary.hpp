#pragma once
#include <map>
#include <vector>
#include "./Exception/DictionaryException.hpp"
#include <iosfwd>
// #include "./ISerializable.hpp"


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

    std::string Serialize() const;
    void Unserialize(std::string & object);

private:
    dict dictRuToEn;
    dict dictEnToRu;

    std::string dictRuToEnName = "RuToEn";
    std::string dictEnToRuName = "EnToRu";

    const std::string DICTIONARY = "Dictionary";

    const char JSON_START_OBJECT = '{';
    const char JSON_END_OBJECT = '}';
    const char JSON_START_ARRAY = '[';
    const char JSON_END_ARRAY = ']';
    const char COMMA_SEPARATOR = ',';
    const char COLON_SEPARATOR = ':';
    const char QUOTES = '"';
    const char SPACE = ' ';
    const char DASH ='-';
    const int YAML_SPACE_OFFSET = 4;

    std::string ConvertStringToJsonNotation(const std::string & value) const;
    std::string ConvertDictToJsonNotaion(const dict & dictionary) const;

    std::string EscapeJsonNotation(std::string & value) const;

    void WriteTranslationIntoDict(std::string & key, const std::string & value, dict & dictionary);
    std::vector<std::string> RetrieveTranslationFromDict(const std::string & key, const dict & dictionary) const;
};
