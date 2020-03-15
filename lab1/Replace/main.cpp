#include <iostream>
#include <fstream>
#include "Command/ReplaceInStream/ReplaceInStream.hpp"

bool OpenFiles(std::ifstream *fin, std::ofstream *fout, std::string firstFileName, std::string secondeFileName);

int main(int argc, char const *argv[])
{
    if (argc < 5)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    std::ifstream fin;
    std::ofstream fout;

    if (!OpenFiles(&fin, & fout, argv[1], argv[2]))
    {
        return 1;
    }

    ReplaceInStream::Execute(&fin, &fout, argv[3], argv[4]);

    return 0;
}

bool OpenFiles(std::ifstream *fin, std::ofstream *fout, std::string firstFileName, std::string secondeFileName)
{
    (*fin).open(firstFileName);
    (*fout).open(secondeFileName);

    if (!(*fin).is_open() || !(*fout).is_open())
    {
        std::cout << "Error to open " << (!(*fin).is_open() ? firstFileName : secondeFileName) << std::endl;
        return false;
    }

    return true;
}
