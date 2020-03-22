#include "./ConvertException.hpp"

ConvertException::ConvertException(std::string msg)
{
    this->msg = msg;
}

const std::string ConvertException::getMsg() const noexcept
{
    return ConvertException::msg;
}

void ConvertException::setMsg(const std::string & msg)
{
    this->msg = msg;
}
