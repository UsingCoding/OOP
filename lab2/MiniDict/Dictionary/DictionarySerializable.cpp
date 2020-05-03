#include "./Dictionary.hpp"
#include "../../../Utils/StringUtils.hpp"
#include <iostream>
#include <stdexcept>

std::string Dictionary::Serialize() const
{
    return StringUtils::MakeString() << DICTIONARY << COLON_SEPARATOR << '\n' << ConvertDictToJsonNotaion(dictEnToRu);
}

std::string Dictionary::ConvertDictToJsonNotaion(const dict & dictionary) const
{
    std::string serializedDict;

    dict::const_iterator it = dictionary.begin();

    for (size_t i = 0; it != dictionary.end(); it++, i++)
    {
        serializedDict += StringUtils::MakeSpaceOffset(YAML_SPACE_OFFSET) + StringUtils::ConvertToJsonNotation(it->first) + COLON_SEPARATOR + '\n';

        for (size_t i = 0; i < it->second.size(); i++)
        {
            serializedDict += StringUtils::MakeSpaceOffset(YAML_SPACE_OFFSET * 2) + DASH + ' ' + StringUtils::ConvertToJsonNotation(it->second[i]) + '\n';
        }
    }

    return serializedDict;
}

void Dictionary::Unserialize(std::istream & input)
{
    std::string dictKeyWord;

    getline(input, dictKeyWord);

    dictKeyWord = dictKeyWord.substr(0, dictKeyWord.length() - 1);

    if (dictKeyWord != DICTIONARY)
    {
        throw std::logic_error("Unknown format - " + dictKeyWord);
    }

    std::string key;
    std::string value;
    bool isDictValueNext = false;

    while (!input.eof())
    {
        getline(input, value);
        value = StringUtils::Trim(value);

        if (IsYamlKey(value))
        {
            std::string handledValue = value.substr(0, value.length() - 1);
            key = StringUtils::EscapeJsonNotation(handledValue);
            continue;
        }

        if (IsYamlArrayValue(value))
        {
            value = value.substr(2, value.length());
            value = StringUtils::EscapeJsonNotation(value);
            WriteTranslationIntoDict(key, value, dictEnToRu);
            WriteTranslationIntoDict(value, key, dictRuToEn);
        }        
    }
}

bool Dictionary::IsYamlKey(const std::string & value) const
{
    return value[value.length() - 1] == COLON_SEPARATOR;
}

bool Dictionary::IsYamlArrayValue(const std::string & value) const
{
    return StringUtils::StartsWith(value, StringUtils::MakeString() << DASH);
}
