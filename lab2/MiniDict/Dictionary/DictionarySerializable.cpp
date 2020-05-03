#include "./Dictionary.hpp"
#include "../../../Utils/StringUtils.hpp"
#include <iostream>
#include <stdexcept>

std::string Dictionary::Serialize() const
{
    std::string serializedDict;

    serializedDict += DICTIONARY + COLON_SEPARATOR + '\n';

    serializedDict += ConvertDictToJsonNotaion(dictEnToRu);

    return serializedDict;
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
