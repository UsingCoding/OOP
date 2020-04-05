#include <iostream>
#include "./Parser/Parser.hpp"

int main(int argc, char const *argv[])
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url;

    while (getline(std::cin, url))
    {
        if (!ParseURL(url, protocol, port, host, document))
        {
            std::cout << "Failed to parse url" << std::endl;
            continue;
        }

        std::cout << url << std::endl;
        std::cout << "HOST: " << host << std::endl;
        std::cout << "PORT: " << port << std::endl;
        std::cout << "DOC: " << document << std::endl;
    }

    return 0;
}
