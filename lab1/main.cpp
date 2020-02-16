#include <iostream>
#include "./Converter/Converter.hpp"

int main(int argc, char const *argv[])
{
    Converter *converter = new Converter;

    if (argc != 4)
    {
        std::cout << "Missing arguments" << std::endl;
    }

    converter->testConvert(argv[1], argv[2], argv[3]);
    // converter->convert(argv[1], argv[2], argv[3]);

    return 0;
}
