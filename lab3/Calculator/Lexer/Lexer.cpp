#include "./Lexer.hpp"
#include "../Syntaxer/Syntaxer.hpp"
#include <iostream>
#include "../../../Utils/StringUtils.hpp"
#include "../../../Utils/VectorUtils.hpp"

bool Lexer::IsTerminalDivider(const char symbol)
{
    switch (symbol)
    {
    case Syntaxer::SPACE:
    case Syntaxer::EQUALS_SIGN:
    case Syntaxer::PLUS_SIGN:
    case Syntaxer::MINUS_SIGN:
    case Syntaxer::MULTIPLY_SIGN:
    case Syntaxer::DIVIDE_SIGN:
        return true;
    default:
        return false;
    }
}

std::vector<std::string> Lexer::RetrieveTokensList(const std::string & value)
{
    std::vector<std::string> result;
    int offset = -1;

    for (size_t i = 0; i < value.length(); i++)
    {
        if (!IsTerminalDivider(value[i]))
        {
            offset = offset == -1 ? 1 : offset + 1;
            continue;
        }
        if (offset != -1)
        {
            result.push_back(value.substr(i - offset, offset));
        }
        
        if (value[i] != Syntaxer::SPACE)
        {
            result.push_back(StringUtils::StringConcatenator() << value[i]);
        }
        
        offset = -1;
    }
    if (offset != -1)
    {
        result.push_back(value.substr(value.length() - offset, offset));
    }

    return result;
}

std::vector<std::string> Lexer::RetrieveTokensList(std::istream & input)
{
    std::vector<std::string> result;

    std::string expression;
    int offset;

    while (!input.eof())
    {
        getline(input, expression);
        std::vector<std::string> tokens = RetrieveTokensList(expression);
        result = VectorUtils::Merge(result, tokens);
    }
    
    return result;
}
