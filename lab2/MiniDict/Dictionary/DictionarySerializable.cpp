#include "./Dictionary.hpp"

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


void Dictionary::Deserialize(std::string object)
{
    
}
