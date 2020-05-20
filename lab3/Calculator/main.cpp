#include <iostream>
#include <memory>
#include "./NodeBuilder/NodeBuilder.hpp"
#include "./Domain/ResourceManger/ResourceManager.hpp"
#include "./CommandLineController/CommandLineController.hpp"

int main(int argc, char const *argv[])
{
    std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();
    std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);

    CommandLineController clc(nodeBuilder, manager);

    clc.Start(std::cin);
   
    return 0;
}
