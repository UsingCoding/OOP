#pragma once
#include <string>
#include "ConverterException.hpp"

class Converter
{
private:
    int stringToInt(std::string *str, int radix, bool  *wasError);
    std::string intToString(int n, int radix, bool *wasError);
    std::string convertFromTenNotTo(int value, int destNot);
    int convertToTenNot(std::string value, int srcNot);
    bool proceedNegative(std::string* value);
public:
    Converter();
    ~Converter();
    int convert(std::string sourceNotation, std::string destNotation, std::string value);

    std::string testConvert(std::string sourceNotation, std::string destNotation, std::string value);
};
