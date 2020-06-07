#include "./MyString/MyString.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    MyString string = "startup";

    std::cout << string;
    std::cin >> string;

    return 0;
}
