#include "./Car.hpp"
#include <iostream>

Car::Car()
{
    isEngineOn = false;
    gear = 0;
    speed = 0;
    direction = Direction::Stand;

    gearbox.push_back(Gear(0, 20, -1));
    gearbox.push_back(Gear(0, 0, 0));
    gearbox.push_back(Gear(0, 30, 1));
    gearbox.push_back(Gear(20, 50, 2));
    gearbox.push_back(Gear(30, 60, 3));
    gearbox.push_back(Gear(40, 90, 4));
    gearbox.push_back(Gear(50, 150, 5));
}

bool Car::Gear::IsInSpeedsRange(int value)
{
    if (number == 0)
    {
        return true;
    }
    
    return minSpeed <= value && value <= maxSpeed;
}

bool Car::IsEngineOn() const
{
    return isEngineOn;
}

std::string Car::GetDirection() const
{
    switch (direction)
    {
    case Direction::Stand:
        return "Stand";
    case Direction::Forward:
        return "Forward";
    default:
        return "Backward";
    };
}

int Car::GetCurrentSpeed() const
{
    return speed;
}

int Car::GetCurrentGear() const
{
    return gear;
}

bool Car::TurnOnEngine()
{
    if (speed != 0 || gear != 0)
    {
        return false;
    }
    
    isEngineOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (speed != 0 || gear != 0)
    {
        return false;
    }
    
    isEngineOn = false;
    return true;
}

bool Car::SetGear(int newGear)
{
    if (newGear >= GetMaxGearCount() || newGear < MIN_GEAR)
    {
        return false;
    }
    
    if (!isEngineOn && newGear != 0)
    {
        return false;
    }

    if (newGear == -1 && speed !=0)
    {
        return false;
    }

    if (gear == -1 && newGear >= 1 && speed != 0)
    {
        return false;
    }

    if (newGear == 1 && gear <= 0 && speed != 0)
    {
        return false;
    }
    
    Gear currentGear = gearbox[newGear + 1];

    if (!currentGear.IsInSpeedsRange(speed))
    {
        return false;
    }

    gear = newGear;    

    if (gear == -1)
    {
        direction = Direction::Backward;
    }
    else if (gear >= 1)
    {
        direction = Direction::Forward;
    }

    return true;
}

bool Car::SetSpeed(int newSpeed)
{
    
    if (!isEngineOn)
    {
        return false;
    }

    if (newSpeed < 0)
    {
        return false;
    }

    if (gear == 0 && newSpeed > speed)
    {
        return false;
    }
    
    Gear currentGear = gearbox[gear + 1];

    if (!currentGear.IsInSpeedsRange(newSpeed))
    {
        return false;
    }

    speed = newSpeed;

    if (speed == 0)
    {
        direction = Direction::Stand;
        return true;
    }
    return true;
}

int Car::GetMaxGearCount() const
{
    return gearbox.size();
}