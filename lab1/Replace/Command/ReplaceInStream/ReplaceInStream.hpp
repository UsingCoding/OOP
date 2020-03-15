#pragma once
#include <iostream>

class ReplaceInStream
{
public:
    void static Execute(std::istream * in, std::ostream * out, std::string searchStr, std::string replaceStr);
};
