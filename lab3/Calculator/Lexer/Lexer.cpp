#include "./Lexer.hpp"
#include <iostream>
#include "../../../Utils/StringUtils.hpp"
#include "../../../Utils/VectorUtils.hpp"

const char Lexer::SPACE = ' ';
const char Lexer::EQUALS_SIGN = '=';

bool Lexer::IsTerminalDivider(const char symbol)
{
    switch (symbol)
    {
    case SPACE:
    case EQUALS_SIGN:
    case PLUS_SIGN:
    case MINUS_SIGN:
    case MULTIPLY_SIGN:
    case DIVIDE_SIGN:
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
        
        if (value[i] != SPACE)
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
