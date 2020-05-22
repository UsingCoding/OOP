#pragma once

#include <vector>
#include <string>

class Car
{
public:
    Car();

    bool IsEngineOn() const;
    std::string GetDirection() const;
    int GetCurrentSpeed() const;
    int GetCurrentGear() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int newGear);
    bool SetSpeed(int newSpeed);

private:
    class Gear
    {
    private:
        int maxSpeed;
        int minSpeed;
        int number;

    public:
        Gear(int minValue, int maxValue, int number): minSpeed(minValue), maxSpeed(maxValue), number(number){}
        bool IsInSpeedsRange(int value);
    };

    enum Direction
    {
        Forward,
        Backward,
        Stand
    };

    std::vector<Gear> gearbox;
    bool isEngineOn;
    int gear;
    int speed;
    Direction direction;
    int GetMaxGearCount() const;
    static const int MIN_GEAR = -1;
};
