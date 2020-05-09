#pragma once

#include <vector>
#include <string>

class Car
{
private:
    class Gear
    {
    private:
        int maxValue;
        int minValue;
        int number;

    public:
        Gear(int minValue, int maxValue, int number): minValue(minValue), maxValue(maxValue), number(number){}
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
    static const int MAX_GEAR = 5;

public:
    Car();

    void Display();

    bool IsEngineOn() const;
    std::string GetDirection() const;
    int GetCurrentSpeed() const;
    int GetCurrentGear() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int newGear);
    bool SetSpeed(int newSpeed);
};
