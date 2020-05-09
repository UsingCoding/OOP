#include "../Car/Car.hpp"
#include <memory>

class CommandLineController
{
private:
    std::unique_ptr<Car> car;

    static const std::string INFO_COMMAND;
    static const std::string ENGINE_ON_COMMAND;
    static const std::string ENGINE_OFF_COMMAND;
    static const std::string SET_GEAR_COMMAND;
    static const std::string SET_SPEED_COMMNAD;

    void InfoCommandHandle();
    void EngineOnCommandHandle();
    void EngineOffCommandHandle();
    void SetGearCommandHandle();
    void SetSpeedCommandHandle();

public:
    CommandLineController(std::unique_ptr<Car> newCar);

    void Start();
};

