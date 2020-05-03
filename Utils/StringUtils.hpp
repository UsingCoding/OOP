#pragma once

#include <iostream>
#include <sstream>

namespace StringUtils
{
    const char QUOTES = '"';
    class StringConcatenator
    {
    private:
        std::stringstream stream;
    public:
        template<class T>
        StringConcatenator& operator<< (const T& arg) 
        {
            stream << arg;
            return *this;
        }

        operator std::string() const
        {
            return stream.str();
        }
    };

    static std::string MakeSpaceOffset(int offset)
    {
        StringConcatenator str;
        for (size_t i = 0; i < offset; i++)
        {
            str << ' ';
        }
        
        return str;
    }

    static std::string ConvertToJsonNotation(const std::string & value)
    {
        return QUOTES + value + QUOTES;
    }

    static std::string EscapeJsonNotation(std::string & value)
    {
        if (value[0] != QUOTES || value[value.length() - 1] != QUOTES)
        {
            throw std::runtime_error("Incorrect JSON notaion");
        }

        return value.substr(1, value.length() - 2);
    }

    static bool StartsWith(const std::string & value, const std::string & beginOfString)
    {
        if (value.length() < beginOfString.length())
        {
            return false;
        }
        
        return value.substr(0, beginOfString.length()) == beginOfString;
    }

    static std::string Trim(const std::string & value)
    {
        const std::string chars = "\t\n\v\f\r ";
        std::string cpValue = value;
        
        cpValue.erase(0, cpValue.find_first_not_of(chars));
        cpValue.erase(cpValue.find_last_not_of(chars) + 1);
        return cpValue;
    }
} // namespace StringUtils