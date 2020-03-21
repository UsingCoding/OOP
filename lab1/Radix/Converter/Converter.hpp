#pragma once
#include <string>
#include "ConverterException.hpp"

std::string IntToString(int value, int destNot);
int StringToInt(std::string value, int srcNot);

bool IsNegative(std::string const & value);
int ParseInt(std::string const & value);

const int MODIFICATOR_FOR_LETTERS = 55;
const int MODIFICATOR_FOR_NUMBERS = 48;
const int MAX_DIGIT = 9;
const int TEN_NOT = 10;
