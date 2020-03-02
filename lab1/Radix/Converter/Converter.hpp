#pragma once
#include <string>
#include "ConverterException.hpp"

class Converter
{
private:
    std::string convertFromDecNotTo(int value, int destNot);
    int convertToDecNot(std::string value, int srcNot);
    void parseNotations(std::string* sourceNotation, std::string* destNotation, int* srcNot, int* destNot);
    bool isNegative(std::string const & value);
    int parseInt(std::string const & value);

    const int MODIFICATOR_FOR_LETTERS = 55;
    const int MODIFICATOR_FOR_NUMBERS = 48;
    const int MAX_DIGIT = 9;
    const int TEN_NOT = 10;
public:
    std::string convert(std::string sourceNotation, std::string destNotation, std::string value);
};
