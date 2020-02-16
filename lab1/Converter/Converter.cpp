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

int Converter::testConvert(std::string sourceNotation, std::string destNotation, std::string value)
{
    int valueTenNotation = convertToTenNot(value, 18);
    std::string resValue = convertFromTenNotTo(valueTenNotation, 2);
    std::cout << resValue << std::endl;
}

int Converter::convertToTenNot(std::string value, int srcNot)
{
    int resNumber = 0;
    int currNum;

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] >= 'A')
        {
            currNum = (int)'F' - 55;
        }
        else
        {
            currNum = (int)value[i] - 48;
        }

        int resPow = pow(srcNot, value.length() - (i + 1));
        if (resPow < 0)
        {
            throw ConverterException("Overflow happend while converting");
        }

        resNumber += currNum * resPow;
    }

    std::cout << resNumber << std::endl;

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
