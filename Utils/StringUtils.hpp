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

public:
    StringUtils() = delete;

    static StringConcatenator MakeString()
    {
        return StringConcatenator();
    }
};