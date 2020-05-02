#include <iostream>
#include "./Decode.hpp"

int main(int argc, char const *argv[])
{
    std::string line;
    while (getline(std::cin, line))
    {
        std::cout << HtmlDecode(line) << std::endl;
    }
    
    return 0;
}

