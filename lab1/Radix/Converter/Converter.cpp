#include "./Converter.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

int StringToInt(const std::string & value, const int & srcNot)
{
    if (srcNot == TEN_NOT)
    {
        return ParseInt(value);
    }

    float resNumber = 0;
    int currNum;

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] >= 'A' && value[i] <= 'Z')
        {
            currNum = (int)value[i] - MODIFICATOR_FOR_LETTERS;
        }
        else
        {
            currNum = (int)value[i] - MODIFICATOR_FOR_NUMBERS;
            if (currNum >= srcNot)
            {
                throw ConverterException("Incorrect number for this notation");
            }

        }

        int resPow = pow(srcNot, value.length() - (i + 1));
        if (resPow < 0)
        {
            throw ConverterException("Overflow happend while converting");
        }

        resNumber += currNum * resPow;
    }

    return resNumber;
}

std::string IntToString(unsigned int value, const int & destNot)
{
    std::string buffer;
    std::string result;
    char currNum;

    while (true)
    {
        currNum = value % destNot;
        if (currNum > MAX_DIGIT)
        {
            currNum = currNum + MODIFICATOR_FOR_LETTERS;
        }
        else
        {
            currNum = currNum + '0';
        }

        buffer += currNum;
        value = value / destNot;

        if (value == 0)
        {
            break;
        }
    }

    for (int i = buffer.size() - 1; i >= 0; i--)
    {
        result += buffer[i];
    }

    return result;
}

bool IsNegative(std::string const & value)
{
    if (value[0] != '-')
    {
        return false;
    }
    return true;
}

int ParseInt(std::string const & value)
{
    try
    {
        return std::stoi(value);
    }
    catch(std::exception exception)
    {
        throw ConverterException("Some bad symbol in number");
    }
}
