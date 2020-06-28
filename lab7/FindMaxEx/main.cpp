#include "FindMaxEx/FindMaxEx.hpp"
#include <vector>
#include <string>
#include <iostream>

struct Sportsman
{
    std::string FIO;
    int growth;
    int weight;
};

int main(int argc, char const *argv[])
{
    std::vector<Sportsman> sportsmans;

    sportsmans.push_back(Sportsman{"Andrey Usulov", 160, 90});
    sportsmans.push_back(Sportsman{"Indro Kenky", 180, 100});
    sportsmans.push_back(Sportsman{"Issaac Ismailov", 140, 60});
    sportsmans.push_back(Sportsman{"Arseni Krailov", 200, 95});

    Sportsman val;

    FindMax(sportsmans, val, [](Sportsman a, Sportsman b) { return a.growth < b.growth; });

    std::cout << val.FIO << std::endl;

    FindMax(sportsmans, val, [](Sportsman a, Sportsman b) { return a.weight < b.weight; });

    std::cout << val.FIO << std::endl;

    return 0;
}
