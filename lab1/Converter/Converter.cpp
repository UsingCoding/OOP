#include "./Converter.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

std::string Converter::convert(std::string sourceNotation, std::string destNotation, std::string value)
{
    bool isNegative = proceedNegative(&value);

    if (value.length() <= 0)
    {
        throw ConverterException("Not enough length of value");
    }

    int srcNot;
    int destNot;

    parseNotations(&sourceNotation, &destNotation, &srcNot, &destNot);


    int valueTenNotation = convertToTenNot(value, srcNot);
    std::string resValue = convertFromTenNotTo(valueTenNotation, destNot);

    return !isNegative ? resValue : "-" + resValue;
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

int Converter::convertToTenNot(std::string value, int srcNot)
{
    float resNumber = 0;
    int currNum;
    int powModificator = value.find_first_of('.', 0);
    powModificator = powModificator == -1 ? value.length() : powModificator;

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] == '.')
        {
            powModificator += 1;
            continue;
        }

        if (value[i] >= 'A')
        {
            currNum = (int)value[i] - Converter::MODIFICATOR_FOR_LETTERS;
        }
        else
        {
            currNum = (int)value[i] - Converter::MODIFICATOR_FOR_NUMBERS;
        }

        int resPow = pow(srcNot, powModificator - (i + 1));
        if (resPow < 0)
        {
            throw ConverterException("Overflow happend while converting");
        }

        resNumber += currNum * resPow;
    }

    return resNumber;
}

std::string Converter::convertFromTenNotTo(int value, int destNot)
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

bool Converter::proceedNegative(std::string* value)
{
    if ((*value)[0] != '-')
    {
        return false;
    }

    (*value).erase(0, 1);
}
