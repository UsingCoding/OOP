#include "StringUtils.hpp"

std::string StringUtils::MakeSpaceOffset(int offset)
{
    StringConcatenator str;
    for (size_t i = 0; i < offset; i++)
    {
        str << SPACE;
    }

    return str;
}

std::string StringUtils::EscapeString(const std::string & value)
{
    return QUOTES + value + QUOTES;
}

std::string StringUtils::UnescapeString(std::string & value)
{
    if (value[0] != QUOTES || value[value.length() - 1] != QUOTES)
    {
        throw std::runtime_error("Failed to unescape, missing quotes");
    }
    return value.substr(1, value.length() - 2);
}

bool StringUtils::StartsWith(const std::string & value, const std::string & beginOfString)
{
    if (value.length() < beginOfString.length())
    {
        return false;
    }

    return value.substr(0, beginOfString.length()) == beginOfString;
}

std::string StringUtils::Trim(const std::string & value)
{
    const std::string chars = "\t\n\v\f\r ";
    std::string cpValue = value;

    cpValue.erase(0, cpValue.find_first_not_of(chars));
    cpValue.erase(cpValue.find_last_not_of(chars) + 1);
    return cpValue;
}
