#include "./Converter.hpp"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

Converter::Converter()
{}

int Converter::convert(std::string sourceNotation, std::string destNotation, std::string value)
{
    bool wasError;

    // int srcNot = stringToInt(&sourceNotation, 10, &wasError);
    // int destNot = stringToInt(&destNotation, 10, &wasError);

    // int valueTenNotation = convertToTenNot(value, srcNot);
    // std::string resValue = convertFromTenNotTo(valueTenNotation, destNot);
}

std::string Converter::testConvert(std::string sourceNotation, std::string destNotation, std::string value)
{
    bool isNegative = proceedNegative(&value);

    if (value.length() <= 0)
    {
        throw ConverterException("Not enough length of value");
    }

    int valueTenNotation = convertToTenNot(value, 16);
    std::string resValue = convertFromTenNotTo(valueTenNotation, 2);

    return !isNegative ? resValue : "-" + resValue;
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
            currNum = (int)value[i] - 55;
        }
        else
        {
            currNum = (int)value[i] - 48;
        }

        float resPow = pow(srcNot, powModificator - (i + 1));
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
        if (currNum > 9)
        {
            currNum = currNum + 55;
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
