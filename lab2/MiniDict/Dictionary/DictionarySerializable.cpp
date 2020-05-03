#include "./Dictionary.hpp"
#include <iostream>
#include <stdexcept>

std::string Dictionary::Serialize() const
{
    std::string enToRuSerialized;

    enToRuSerialized += ConvertStringToJsonNotation(dictEnToRuName) + COLON_SEPARATOR + JSON_START_OBJECT + ConvertDictToJsonNotaion(dictEnToRu) + JSON_END_OBJECT;

    std::string ruToEnSerialized;

    ruToEnSerialized += ConvertStringToJsonNotation(dictRuToEnName) + COLON_SEPARATOR + JSON_START_OBJECT + ConvertDictToJsonNotaion(dictRuToEn) + JSON_END_OBJECT;

    return JSON_START_OBJECT + enToRuSerialized + COMMA_SEPARATOR + ruToEnSerialized + JSON_END_OBJECT;
}

std::string Dictionary::ConvertStringToJsonNotation(const std::string & value) const
{
    return QUOTES + value + QUOTES;
}

std::string Dictionary::ConvertDictToJsonNotaion(const dict & dictionary) const
{
    std::string serializedDict;

    dict::const_iterator it = dictionary.begin();

    for (size_t i = 0; it != dictionary.end(); it++, i++)
    {
        serializedDict += ConvertStringToJsonNotation(it->first) + COLON_SEPARATOR + JSON_START_ARRAY;

        for (size_t i = 0; i < it->second.size(); i++)
        {
            serializedDict += ConvertStringToJsonNotation(it->second[i]);

            if (i != it->second.size() - 1)
            {
                serializedDict += COMMA_SEPARATOR;
            }
        }

        serializedDict += JSON_END_ARRAY;

        if (i != dictionary.size() - 1)
        {
            serializedDict += COMMA_SEPARATOR;
        }
    }

    return serializedDict;
}

std::string Dictionary::EscapeJsonNotation(std::string & value) const
{
    if (value[0] != QUOTES && value[value.length() - 1] != QUOTES)
    {
        throw std::runtime_error("Incorrect JSON notaion");
    }
    
    return value.substr(1, value.length() - 2);
}

void Dictionary::Unserialize(std::string & object)
{
    int state;

    for (size_t i = 0; i < object.length(); i++)
    {
        if (object[i] == ' ' || object[i] == '\n')
        {
            continue;
        }

        if (object[i] != JSON_START_OBJECT && i == 0)
        {
            throw std::runtime_error("Incorrect JSON notaion");
        }

        object.find(JSON_START_OBJECT, i);
        
    }
}
