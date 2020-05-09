#include <iostream>
#include "./Car/Car.hpp"

int main(int argc, char const *argv[])
{
    Car car;
    car.TurnOnEngine();
    car.SetGear(-1);
    car.SetSpeed(10);
    car.SetSpeed(0);
    std::cout << "res " << car.TurnOffEngine() << std::endl;
    
    car.Display();
    return 0;
}
