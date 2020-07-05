#include "Stack/Stack.hpp"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
    StringStack stack;

    stack.Push("stack");
    stack.Push("Slack");

    std::cout << stack.Pop() << std::endl;
    std::cout << stack.Pop() << std::endl;

    return 0;
}
