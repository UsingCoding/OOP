#pragma once
#include <string>

class CommandException
{
private:
    std::string msg;
public:
    CommandException(std::string msg);
    const std::string GetMessage() const noexcept;
};
