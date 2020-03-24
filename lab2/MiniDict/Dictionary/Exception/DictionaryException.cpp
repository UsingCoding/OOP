#include "./DictionaryException.hpp"

DictionaryException::DictionaryException(const char* measage)
{
    this->message = message;
}

const char* DictionaryException::what() const noexcept
{
    return message;
}
