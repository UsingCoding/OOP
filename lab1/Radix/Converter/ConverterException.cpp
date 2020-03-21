#include "./ConverterException.hpp"

ConverterException::ConverterException(std::string msg)
{
    this->msg = msg;
}

const std::string ConverterException::getMsg() const noexcept
{
    return ConverterException::msg;
}

void ConverterException::setMsg(const std::string & msg)
{
    this->msg = msg;
}

static ConverterException convertOverflowError()
{
    return ConverterException("Overflow happend when converting");
}
