#include "./Convert.hpp"
#include <iostream>
#include <cmath>

int StringToInt(const std::string & value, int srcNot)
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
                throw ConvertException("Incorrect number for this notation");
            }

        }

        resNumber = (resNumber + currNum) * (i != value.length() - 1 ? srcNot : 1);
    }

    return resNumber;
}

std::string IntToString(unsigned int value, int destNot)
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

bool IsNegative(const std::string & value)
{
    if (value[0] != '-')
    {
        return false;
    }
    return true;
}

int ParseInt(const std::string & value)
{
    try
    {
        return std::stoi(value);
    }
    catch(std::exception exception)
    {
        throw ConvertException("Some bad symbol in number");
    }
}
