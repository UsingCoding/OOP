#pragma once
#include <string>

class ReadException
{
private:
    std::string msg;
public:
    ReadException(std::string msg);
    const std::string GetMessage() const noexcept;
};
