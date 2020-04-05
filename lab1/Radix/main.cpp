#include <iostream>
#include "./Convert/Convert.hpp"
#include <exception>
#include <stdexcept>

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        std::cout << "Missing arguments, need to pass 3 arguments" << std::endl;
        return 1;
    }

    int srcNot;
    int destNot;

    try
    {
        srcNot = ParseInt(argv[1]);
        destNot = ParseInt(argv[2]);
    }
    catch(const ConvertException & e)
    {
        std::cerr << "Incorrect symbol in notation" << std:: endl;
        return 1;
    }

    try
    {
        std::cout << Convert(argv[3], srcNot, destNot) << std::endl;

    }
    catch (const ConvertException & e)
    {
        std::cerr << e.getMsg() << std::endl;
        return 1;
    }

    return 0;
}
