#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

#include "../Car/Car/Car.hpp"

SCENARIO("Turning on engine and off on zero speed and neutral gear")
{
    GIVEN("New car")
    {
        Car car;

        WHEN("We turning on engine")
        {
            bool res = car.TurnOnEngine();
            THEN("We got true from car and enine is turned on")
            {
                REQUIRE(res == true);
                REQUIRE(car.IsEngineOn() == true);
            }

            AND_WHEN("We turning off engine")
            {
                bool res = car.TurnOffEngine();
                THEN("We got true from car and engine is turned off")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.IsEngineOn() == false);
                }
            }
        }
    }
}

SCENARIO("Turning on engine and ride on first gear on 20 km/h")
{
    GIVEN("New car")
    {
        Car car;

        WHEN("We turning on engine")
        {
            bool res = car.TurnOnEngine();
            THEN("We got true from car and enine is turned on")
            {
                REQUIRE(res == true);
                REQUIRE(car.IsEngineOn() == true);
            }

            AND_WHEN("We set speed at 25")
            {
                bool res = car.SetSpeed(25);
                THEN("We get false from car and speed is still a 0")
                {
                    REQUIRE(res == false);
                    REQUIRE(car.GetCurrentSpeed() == 0);
                }
            }

            AND_WHEN("We set first gear")
            {
                bool res = car.SetGear(1);
                THEN("We got true from car and gear is 1")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.GetCurrentGear() == 1);
                }

                AND_WHEN("We set speed at 20")
                {
                    bool res = car.SetSpeed(20);
                    THEN("We got true from car and speed is 20 and direction is forward")
                    {
                        REQUIRE(res == true);
                        REQUIRE(car.GetCurrentSpeed() == 20);
                        REQUIRE(car.GetDirection() == "Forward");
                    }
                }

                AND_WHEN("We set speed at 40(more than first gear can handle)")
                {
                    bool res = car.SetSpeed(40);
                    THEN("We got false from car and speed is 0 and gear is 1")
                    {
                        REQUIRE(res == false);
                        REQUIRE(car.GetCurrentSpeed() == 0);
                        REQUIRE(car.GetCurrentGear() == 1);
                    }
                }
            }
        }
    }
}

SCENARIO("Stopping car and turning off engine")
{
    GIVEN("Car with second gear and speed is 50 km/h")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(50);

        WHEN("We set speed at zero")
        {
            bool res = car.SetSpeed(0);

            THEN("We got false from and speed is 50, gear is 2")
            {
                REQUIRE(res == false);
                REQUIRE(car.GetCurrentSpeed() == 50);
                REQUIRE(car.GetCurrentGear() == 2);
            }
        }

        WHEN("We set first gear")
        {
            bool res = car.SetGear(1);
            THEN("We got false from car and didn`t change speed and gear")
            {
                REQUIRE(res == false);
                REQUIRE(car.GetCurrentSpeed() == 50);
                REQUIRE(car.GetCurrentGear() == 2);
            }
        }

        WHEN("We set speed at 25 and second gear")
        {
            bool res = car.SetSpeed(25);
            THEN("We got true from car and speed now is 25")
            {
                REQUIRE(res == true);
                REQUIRE(car.GetCurrentSpeed() == 25);
                REQUIRE(car.GetCurrentGear() == 2);
            }

            AND_WHEN("We set first gear")
            {
                bool res = car.SetGear(1);
                THEN("We got true from car and gear is 1")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.GetCurrentGear() == 1);
                }
            }

            AND_WHEN("We set neutral gear and zero speed")
            {
                car.SetGear(0);
                bool res = car.SetSpeed(0);
                THEN("We got true from car and car stopped")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.GetCurrentSpeed() == 0);
                }

                AND_WHEN("We turning off engine")
                {
                    bool res = car.TurnOffEngine();
                    THEN("We got true from car and engine is turned off")
                    {
                        REQUIRE(res == true);
                        REQUIRE(car.IsEngineOn() == false);
                    }
                }
            }

            AND_WHEN("We set neutral gear and zero speed")
            {
                car.SetGear(0);
                bool res = car.SetSpeed(0);
                THEN("We got true from car and car stopped")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.GetCurrentSpeed() == 0);
                }

                AND_WHEN("We turning off engine")
                {
                    bool res = car.TurnOffEngine();
                    THEN("We got true from car and engine is turned off")
                    {
                        REQUIRE(res == true);
                        REQUIRE(car.IsEngineOn() == false);
                    }
                }
            }
        }
    }
}

SCENARIO("Riding backward and stopping")
{
    GIVEN("Car with turned on engine")
    {
        Car car;
        car.TurnOnEngine();

        WHEN("We set -1 gear")
        {
            bool res = car.SetGear(-1);
            THEN("We got true from car and gear is -1")
            {
                REQUIRE(res == true);
                REQUIRE(car.GetCurrentGear() == -1);
            }

            AND_WHEN("We set speed at 10")
            {
                bool res = car.SetSpeed(10);
                THEN("We got true and speed is 10 and direction is backward")
                {
                    REQUIRE(res == true);
                    REQUIRE(car.GetCurrentSpeed() == 10);
                    REQUIRE(car.GetDirection() == "Backward");
                }

                AND_WHEN("We turning off engine")
                {
                    bool res = car.TurnOffEngine();
                    THEN("We got false and engine still on and spped is 10")
                    {
                        REQUIRE(res == false);
                        REQUIRE(car.IsEngineOn() == true);
                        REQUIRE(car.GetCurrentSpeed() == 10);
                    }
                }

                AND_WHEN("We stopped car")
                {
                    bool res = car.SetSpeed(0);
                    THEN("We got true and speed is 0")
                    {
                        REQUIRE(res == true);
                        REQUIRE(car.GetCurrentSpeed() == 0);
                    }

                    AND_WHEN("We turned off engine")
                    {
                        bool res = car.TurnOffEngine();
                        THEN("We got false and engine still on")
                        {
                            REQUIRE(res == false);
                            REQUIRE(car.IsEngineOn() == true);
                        }
                    }

                    AND_WHEN("We set neutral gear and turning off engine")
                    {
                        car.SetGear(0);
                        bool res = car.TurnOffEngine();
                        THEN("We got true and engine is turned off")
                        {
                            REQUIRE(res == true);
                            REQUIRE(car.IsEngineOn() == false);
                        }
                    }
                }
            }

            AND_WHEN("we set speed at 30")
            {
                bool res = car.SetSpeed(30);
                THEN("We got false and speed is 0")
                {
                    REQUIRE(res == false);
                    REQUIRE(car.GetCurrentSpeed() == 0);
                }
            }
        }
    }
}

SCENARIO("Changing gears on differnt speeds")
{
    GIVEN("New car with turned on engine")    
    {
        Car car;
        car.TurnOnEngine();

        WHEN("We set gear at -1 and speed at 10")
        {
            car.SetGear(-1);
            car.SetSpeed(10);

            AND_WHEN("We set neutral gear")
            {
                car.SetGear(0);

                THEN("We can`t set -1 gear")
                {
                    REQUIRE(!car.SetGear(-1));
                }

                THEN("We can`t set 1 gear")
                {
                    REQUIRE(!car.SetGear(1));
                }

                AND_WHEN("We set zero speed")
                {
                    car.SetSpeed(0);

                    THEN("We can set -1 gear")
                    {
                        REQUIRE(car.SetGear(-1));
                    }

                    THEN("We can set 1 gear")
                    {
                        REQUIRE(car.SetGear(1));
                    }
                }
            }
        }

        WHEN("We set first gear and speed at 15")
        {
            car.SetGear(-1);
            car.SetSpeed(10);

            THEN("We can`t set -1 gear")
            {
                REQUIRE(!car.SetGear(-1));
            }
        }

        WHEN("We trying to set -2 gear")
        {
            bool res = car.SetGear(-2);

            THEN("We can`t do it")
            {
                REQUIRE(!res);
            }
        }

        WHEN("We trying to set speed at -20")
        {
            bool res = car.SetSpeed(-20);

            THEN("We can`t do it")
            {
                REQUIRE(!res);
            }
        }
    }
}
