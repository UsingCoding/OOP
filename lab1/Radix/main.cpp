#include <iostream>
#include "./Converter/Converter.hpp"
#include <exception>
#include <stdexcept>

int main(int argc, char const *argv[])
{
    Converter converter;

    if (argc != 4)
    {
        std::cout << "Missing arguments" << std::endl;
    }

    try
    {
        std::cout << converter.Convert(argv[1], argv[2], argv[3]) << std::endl;
    }
    catch (ConverterException converterException)
    {
        std::cerr << converterException.getMsg() << '\n';
    }

    return 0;
}
