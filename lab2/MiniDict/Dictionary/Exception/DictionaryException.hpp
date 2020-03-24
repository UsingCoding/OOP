#pragma once
#include <exception>

class DictionaryException: std::exception
{
private:
    const char* message;
public:
    DictionaryException(const char* message);
    const char* what() const noexcept;
};
