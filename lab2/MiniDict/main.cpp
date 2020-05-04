#include <iostream>
#include "./Dictionary/Dictionary.hpp"
#include "./CommandLineController/CommandLineController.hpp"

#include <memory>
#include <fstream>

int main(int argc, char const *argv[])
{
    std::unique_ptr<Dictionary> dict = std::make_unique<Dictionary>();

    CommandLineController clc(std::move(dict));

    clc.Start();

    return 0;
}
