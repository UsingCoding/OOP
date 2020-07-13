#include "Stack/HStack.hpp"
#include <string>
#include <iostream>


int main(int argc, char const *argv[])
{
    HStack<std::string> stack;

    stack.Push("stack");
    stack.Push("Slack");

    HStack<std::string> stack1 = stack;

    try
    {
        std::cout << stack.Pop() << std::endl;
        std::cout << stack.Pop() << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    std::cout << stack1.Pop() << std::endl;
    std::cout << stack1.Pop() << std::endl;


    return 0;
}
