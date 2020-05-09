#include <iostream>
#include <memory>
#include "./Car/Car.hpp"
#include "./CommandLineController/CommandLineController.hpp"

int main(int argc, char const *argv[])
{
    // std::unique_ptr<Car> car = ;
    CommandLineController clc(std::make_unique<Car>());
    clc.Start();
    return 0;
}
