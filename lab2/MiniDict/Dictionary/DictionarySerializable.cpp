#include "./Dictionary.hpp"
#include "../../../Utils/StringUtils.hpp"
#include <iostream>
#include <stdexcept>

const char Dictionary::COLON_SEPARATOR = ':';
const char Dictionary::DASH = '-';
const int Dictionary::YAML_SPACE_OFFSET = 4;
const std::string Dictionary::DICTIONARY = "Dictionary";

std::string Dictionary::Serialize() const
{
    return StringUtils::StringConcatenator() << DICTIONARY << Dictionary::COLON_SEPARATOR << '\n' << EscapeDict(dictEnToRu);
}

std::string Dictionary::EscapeDict(const dict & dictionary)
{
    std::string serializedDict;

    dict::const_iterator it = dictionary.begin();

    for (size_t i = 0; it != dictionary.end(); it++, i++)
    {
        serializedDict += StringUtils::MakeSpaceOffset(YAML_SPACE_OFFSET) + StringUtils::EscapeString(it->first) + COLON_SEPARATOR + '\n';

        for (size_t i = 0; i < it->second.size(); i++)
        {
            serializedDict += StringUtils::MakeSpaceOffset(YAML_SPACE_OFFSET * 2) + DASH + StringUtils::SPACE + StringUtils::EscapeString(it->second[i]) + '\n';
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

    while (!input.eof())
    {
        getline(input, value);
        value = StringUtils::Trim(value);

        if (value.length() == 0) continue;    

        if (IsKey(value))
        {
            value = value.substr(0, value.length() - 1);
            key = StringUtils::UnescapeString(value);
            continue;
        }

        if (IsArrayValue(value))
        {
            value = value.substr(2, value.length());
            value = StringUtils::UnescapeString(value);
            WriteTranslationIntoDict(key, value, dictEnToRu);
            WriteTranslationIntoDict(value, key, dictRuToEn);
            continue;
        }
        
        throw std::logic_error("Unknown format indentation");
    }
}

bool Dictionary::IsKey(const std::string & value)
{
    return value[value.length() - 1] == COLON_SEPARATOR;
}

bool Dictionary::IsArrayValue(const std::string & value)
{
    return StringUtils::StartsWith(value, StringUtils::StringConcatenator() << DASH);
}
