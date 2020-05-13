#pragma once

#include <vector>
#include <string>
#include <iosfwd>

class Lexer
{
private:
    static bool IsTerminalDivider(const char symbol);
public:
    static std::vector<std::string> RetrieveTokensList(const std::string & value);
    static std::vector<std::string> RetrieveTokensList(std::istream & input);
};
