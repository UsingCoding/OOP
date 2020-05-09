#include "./CommandLineController.hpp"
#include <iostream>
#include <algorithm>

const std::string CommandLineController::INFO_COMMAND = "info";
const std::string CommandLineController::ENGINE_ON_COMMAND = "engineon";
const std::string CommandLineController::ENGINE_OFF_COMMAND = "engineoff";
const std::string CommandLineController::SET_GEAR_COMMAND = "setgear";
const std::string CommandLineController::SET_SPEED_COMMNAD = "setspeed";

CommandLineController::CommandLineController(std::unique_ptr<Car> newCar)
{
    car = std::move(newCar);
}

void CommandLineController::Start()
{
    std::cout << "Your new Bentley just created. Type commands to ride on your car" << std::endl;
    std::string userIn;

    while (true)
    {
        std::cout << "Enter a command" << std::endl << ">> ";
        std::cin >> userIn;

        std::transform(userIn.begin(), userIn.end(), userIn.begin(), tolower);
        
        if (userIn == INFO_COMMAND)
        {
            InfoCommandHandle();
            continue;
        }

        if (userIn == ENGINE_ON_COMMAND)
        {
            EngineOnCommandHandle();
            continue;
        }

        if (userIn == ENGINE_OFF_COMMAND)
        {
            EngineOffCommandHandle();
            continue;
        }

        if (userIn == SET_GEAR_COMMAND)
        {
            SetGearCommandHandle();
            continue;
        }

        if (userIn == SET_SPEED_COMMNAD)
        {
            SetSpeedCommandHandle();
            continue;
        }
        
        std::cout << "Unknown command" << std::endl;
    }   
}

void CommandLineController::InfoCommandHandle()
{
    std::cout << "IsEngineOn - " << car->IsEngineOn() << std::endl;
    std::cout << "Gear - " << car->GetCurrentGear() << std::endl;
    std::cout << "Speed - " << car->GetCurrentSpeed() << std::endl;
    std::cout << "Direction - " << car->GetDirection() << std::endl;
}

void CommandLineController::EngineOnCommandHandle()
{
    if (car->TurnOnEngine())
    {
        std::cout << "Engine is on" << std::endl;
        return;
    }
    
    std::cout << "Failed to turn on engine" << std::endl;
}

void CommandLineController::EngineOffCommandHandle()
{
    if (car->TurnOffEngine())
    {
        std::cout << "Engine is off" << std::endl;
        return;
    }

    std::cout << "Failed to turn off engine" << std::endl;
}

void CommandLineController::SetGearCommandHandle()
{
    int gear;
    std::cin >> gear;

    if (car->SetGear(gear))
    {
        std::cout << "Gear is setted" << std::endl;
        return;
    }

    std::cout << "Failed to set gear" << std::endl;
}

void CommandLineController::SetSpeedCommandHandle()
{
    int speed;
    std::cin >> speed;

    if (car->SetSpeed(speed))
    {
        std::cout << "Speed is setted" << std::endl;
        return;
    }

    std::cout << "Failed to set speed" << std::endl;
}
