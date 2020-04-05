#pragma once
#include <string>
#include "ConvertException.hpp"

std::string Convert(const std::string & value, int srcNot, int destNot);

static int StringToInt(const std::string & value, int srcNot);
static std::string IntToString(unsigned int value, int destNot);

static bool IsNegative(const std::string & value);
int ParseInt(const std::string & value);

static const int MODIFICATOR_FOR_LETTERS = 55;
static const int MODIFICATOR_FOR_NUMBERS = 48;
static const int MAX_DIGIT = 9;
static const int TEN_NOT = 10;
