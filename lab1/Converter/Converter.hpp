#pragma once
#include <string>
#include <exception>
#include <stdexcept>

class Converter
{
private:
    int stringToInt(std::string *str, int radix, bool  *wasError);
    std::string intToString(int n, int radix, bool *wasError);
    std::string convertFromTenNotTo(int value, int destNot);
    int convertToTenNot(std::string value, int srcNot);
public:
    Converter();
    ~Converter();
    int convert(std::string sourceNotation, std::string destNotation, std::string value);

    int testConvert(std::string sourceNotation, std::string destNotation, std::string value);
};


class ConverterException
{
private:
    const std::string msg;
public:
    ConverterException();
    std::string getMsg();
};
