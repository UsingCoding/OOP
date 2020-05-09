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

    static const std::string DICTIONARY;
    static const char COLON_SEPARATOR;
    static const char DASH;
    static const int YAML_SPACE_OFFSET;

    static std::string EscapeDict(const dict & dictionary);

    static bool IsKey(const std::string & value);
    static bool IsArrayValue(const std::string & value);

    void WriteTranslationIntoDict(std::string & key, const std::string & value, dict & dictionary);
    std::vector<std::string> RetrieveTranslationFromDict(const std::string & key, const dict & dictionary) const;
};
