#pragma once

#include <iostream>
#include <sstream>

class StringUtils
{
private:
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

    static const char QUOTES = '"';
public:
    StringUtils() = delete;

    static StringConcatenator MakeString()
    {
        return StringConcatenator();
    }

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
        if (value[0] != QUOTES && value[value.length() - 1] != QUOTES)
        {
            throw std::runtime_error("Incorrect JSON notaion");
        }
        
        return value.substr(1, value.length() - 2);
    }
};