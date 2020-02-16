#include "./ConverterException.h"

ConverterException::ConverterException(std::string msg)
{
    ConverterException::msg = msg;
}

std::string ConverterException::getMsg()
{
    return ConverterException::msg;
}

static ConverterException convertOverflowError()
{
    return ConverterException("Overflow happend when converting");
}
