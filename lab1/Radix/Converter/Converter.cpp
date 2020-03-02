#include "./Converter.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

std::string Converter::Convert(std::string sourceNotation, std::string destNotation, std::string value)
{
    if (value.length() <= 0)
    {
        throw ConverterException("Not enough length of value");
    }

    bool isNeg = IsNegative(value);

    if (isNeg)
    {
        value.erase(0, 1);
    }

    int srcNot = ParseInt(sourceNotation);
    int destNot = ParseInt(destNotation);

    if (!(2 <= srcNot && srcNot <= 36) || !(2 <= destNot && destNot <= 36))
    {
        throw ConverterException("Incorrect notation");
    }

    int valueTenNotation = ConvertToDecNot(value, srcNot);
    std::string resValue = ConvertFromDecNotTo(valueTenNotation, destNot);

    return !isNeg ? resValue : "-" + resValue;
}

int Converter::ConvertToDecNot(std::string value, int srcNot)
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
            currNum = (int)value[i] - Converter::MODIFICATOR_FOR_LETTERS;
        }
        else
        {
            currNum = (int)value[i] - Converter::MODIFICATOR_FOR_NUMBERS;
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

std::string Converter::ConvertFromDecNotTo(int value, int destNot)
{
    std::string buffer = "";
    std::string result;
    char currNum;

    while (true)
    {
        currNum = value % destNot;
        if (currNum > Converter::MAX_DIGIT)
        {
            currNum = currNum + Converter::MODIFICATOR_FOR_LETTERS;
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

bool Converter::IsNegative(std::string const & value)
{
    if (value[0] != '-')
    {
        return false;
    }
    return true;
}

int Converter::ParseInt(std::string const & value)
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
