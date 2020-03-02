#include "./Converter.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

std::string Converter::convert(std::string sourceNotation, std::string destNotation, std::string value)
{
    if (value.length() <= 0)
    {
        throw ConverterException("Not enough length of value");
    }

    bool isNeg = isNegative(value);

    if (isNeg)
    {
        value.erase(0, 1);
    }

    int srcNot = parseInt(sourceNotation);
    int destNot = parseInt(destNotation);

    if (!(2 <= srcNot && srcNot <= 36) || !(2 <= destNot && destNot <= 36))
    {
        throw ConverterException("Incorrect notation");
    }

    int valueTenNotation = convertToDecNot(value, srcNot);
    std::string resValue = convertFromDecNotTo(valueTenNotation, destNot);

    return !isNeg ? resValue : "-" + resValue;
}

void Converter::parseNotations(std::string* sourceNotation, std::string* destNotation, int* srcNot, int* destNot)
{
    try
    {
        *srcNot = std::stoi(*sourceNotation);
        *destNot = std::stoi(*destNotation);
    }
    catch(std::exception exception)
    {
        throw ConverterException("Some bad symbol in notation");
    }

    if (!(2 <= *srcNot && *srcNot <= 36) || !(2 <= *destNot && *destNot <= 36))
    {
        throw ConverterException("Incorrect notation");
    }
}

int Converter::convertToDecNot(std::string value, int srcNot)
{
    if (srcNot == TEN_NOT)
    {
        return parseInt(value);
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

std::string Converter::convertFromDecNotTo(int value, int destNot)
{
    std::vector<char> vectorString;
    std::string resString;
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

        vectorString.push_back(currNum);
        value = value / destNot;
        if (value == 0)
        {
            break;
        }
    }

    for (int i = vectorString.size() - 1; i >= 0; i--)
    {
        resString += vectorString[i];
    }

    return resString;
}

bool Converter::isNegative(std::string const & value)
{
    if (value[0] != '-')
    {
        return false;
    }
    return true;
}

int Converter::parseInt(std::string const & value)
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
