#include <iostream>
#include <memory>
#include "./NodeBuilder/NodeBuilder.hpp"
#include "./Infrastructure/ResourceManger/ResourceManager.hpp"
#include "./Interpreter/Interpreter.hpp"

int main(int argc, char const *argv[])
{
    std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
    std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

    Interpreter interpreter(nodeBuilder, manager);

    std::string userIn;

    while (getline(std::cin, userIn))
    {
        std::cout << interpreter.Handle(userIn) << std::endl;
    }

    return 0;
}
