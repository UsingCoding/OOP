#include "ReadException.hpp"

ReadException::ReadException(std::string message)
{
    msg = message;
}

const std::string ReadException::GetMessage() const noexcept
{
    return msg;
}
