#include "CommandException.hpp"

CommandException::CommandException(std::string message)
{
    msg = message;
}

const std::string CommandException::GetMessage() const noexcept
{
    return msg;
}
