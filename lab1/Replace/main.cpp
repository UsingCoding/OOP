#include <iostream>
#include <fstream>
#include "Replacer/Replacer.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 5)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }

    std::ifstream fin;
    std::ofstream fout;

    fin.open(argv[1]);
    fout.open(argv[2]);

    if (!fin.is_open() || !fout.is_open())
    {
        std::cout << "Error to open " << (!fin.is_open() ? argv[1] : argv[2]) << std::endl;
        return 0;
    }

    Replacer *replacer = new Replacer(&fin, &fout, argv[3], argv[4]);
    replacer->execute();

    delete replacer;

    return 0;
}
