#pragma once
#include <string>
#include "ConverterException.hpp"

class Converter
{
private:
    std::string convertFromTenNotTo(int value, int destNot);
    int convertToTenNot(std::string value, int srcNot);
    bool proceedNegative(std::string* value);
    void parseNotations(std::string* sourceNotation, std::string* destNotation, int* srcNot, int* destNot);

    const int MODIFICATOR_FOR_LETTERS = 55;
    const int MODIFICATOR_FOR_NUMBERS = 48;
    const int MAX_DIGIT = 9;
public:
    std::string convert(std::string sourceNotation, std::string destNotation, std::string value);
};
