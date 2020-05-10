#pragma once

#include <vector>
#include <string>
#include <iosfwd>

class Lexer
{
private:
    static const char SPACE = ' ';
    static const char EQUALS_SIGN = '=';
    static const char PLUS_SIGN = '+';
    static const char MINUS_SIGN = '-';
    static const char MULTIPLY_SIGN = '*';
    static const char DIVIDE_SIGN = '/';

    static bool IsTerminalDivider(const char symbol);
public:
    static std::vector<std::string> RetrieveTokensList(const std::string & value);
    static std::vector<std::string> RetrieveTokensList(std::istream & input);
};
