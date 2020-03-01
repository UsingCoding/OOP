#pragma once
#include <fstream>
#include <string>
#include <iostream>

class Replacer
{
private:
    std::ifstream* fin;
    std::ofstream* fout;
    std::string searchStr;
    std::string replaceStr;
    int offset;

public:
    Replacer(std::ifstream *fin, std::ofstream *fout, std::string searchStr, std::string replaceStr);
    ~Replacer();

    void execute();
};
