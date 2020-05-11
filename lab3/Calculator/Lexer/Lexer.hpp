#pragma once

#include <vector>
#include <string>
#include <iosfwd>

class Lexer
{
private:
    static bool IsTerminalDivider(const char symbol);
public:
    static const char SPACE;
    static const char EQUALS_SIGN;
    static constexpr char PLUS_SIGN = '+';
    static constexpr char MINUS_SIGN = '-';
    static constexpr char MULTIPLY_SIGN = '*';
    static constexpr char DIVIDE_SIGN = '/';

    static std::vector<std::string> RetrieveTokensList(const std::string & value);
    static std::vector<std::string> RetrieveTokensList(std::istream & input);
};
