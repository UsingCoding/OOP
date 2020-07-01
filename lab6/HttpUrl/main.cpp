#include <iostream>
#include <string>

#include "HttpUrl/HttpUrl.hpp"

int main(int argc, char const *argv[])
{
    std::string input;

    while (getline(std::cin, input))
    {
        try
        {
            HttpUrl url(input);

            std::cout << url.GetProtocol() << std::endl;
            std::cout << url.GetDomain() << std::endl;
            std::cout << url.GetPort() << std::endl;
            std::cout << url.GetDocument() << std::endl;
            std::cout << url.GetURL() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
