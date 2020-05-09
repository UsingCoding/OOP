#pragma once
#include <map>
#include <vector>
#include "./Exception/DictionaryException.hpp"
#include <iosfwd>
// #include "./ISerializable.hpp"


class Dictionary
{
public:
    enum Locale {
        RU,
        EN
    };

    static const std::string EN_LOCALE;
    static const std::string RU_LOCALE;

    std::vector<std::string> RetrieveTranslation(std::string & key, const Locale & destLocale) const;
    void AddTranslation(std::string & key, std::string & value, const Locale & destLocale);

    std::string Serialize() const;
    void Unserialize(std::istream & input);

    Locale RetrieveLocaleFromString(const std::string & locale);

private:
    typedef std::map<std::string, std::vector<std::string>> dict;
    dict dictRuToEn;
    dict dictEnToRu;

    const std::string DICTIONARY = "Dictionary";
    const char COLON_SEPARATOR = ':';
    const char DASH = '-';
    const int YAML_SPACE_OFFSET = 4;

    std::string EscapeDictToYml(const dict & dictionary) const;

    bool IsYamlKey(const std::string & value);
    bool IsYamlArrayValue(const std::string & value);

    void WriteTranslationIntoDict(std::string & key, const std::string & value, dict & dictionary);
    std::vector<std::string> RetrieveTranslationFromDict(const std::string & key, const dict & dictionary) const;
};
