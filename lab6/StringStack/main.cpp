#include "Stack/Stack.hpp"
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
    Stack<std::string> stack;

    stack.Push("stack");
    stack.Push("Slack");
    stack.Push("Smack");

    Stack<std::string> stack1 = stack;

    return 0;
}
