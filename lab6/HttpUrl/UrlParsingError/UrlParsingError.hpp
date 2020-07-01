#pragma once

#include <stdexcept>
#include <string>

class UrlParsingError : public std::invalid_argument
{
private:
    std::string message;
public:
    // explicit UrlParsingError(const std::string & message): message(message) {}
};
