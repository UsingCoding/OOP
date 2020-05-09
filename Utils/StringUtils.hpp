#pragma once

#include <sstream>

namespace StringUtils
{
    const char QUOTES = '"';
    const char SPACE = ' ';
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

    std::string MakeSpaceOffset(int offset);

    std::string EscapeString(const std::string & value);

    std::string UnescapeString(std::string & value);

    bool StartsWith(const std::string & value, const std::string & beginOfString);

    std::string Trim(const std::string & value);
} // namespace StringUtils