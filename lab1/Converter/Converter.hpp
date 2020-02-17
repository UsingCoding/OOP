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

    const int MODIFICATOR_FOR_LETTERS = 55;
    const int MODIFICATOR_FOR_NUMBERS = 48;
    const int MAX_DIGIT = 9;
public:
    std::string convert(std::string sourceNotation, std::string destNotation, std::string value);
};
