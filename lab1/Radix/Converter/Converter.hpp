#pragma once
#include <string>
#include "ConverterException.hpp"

std::string IntToString(unsigned int value, const int & destNot);
int StringToInt(const std::string & value, const int & srcNot);

bool IsNegative(std::string const & value);
int ParseInt(std::string const & value);

static const int MODIFICATOR_FOR_LETTERS = 55;
static const int MODIFICATOR_FOR_NUMBERS = 48;
static const int MAX_DIGIT = 9;
static const int TEN_NOT = 10;
