#include "Replacer.hpp"

Replacer::Replacer(std::ifstream *fin, std::ofstream *fout, std::string searchStr, std::string replaceStr)
{
    this->fin = fin;
    this->fout = fout;
    this->searchStr = searchStr;
    this->replaceStr = replaceStr;
    offset = 0;
}

Replacer::~Replacer()
{

}

void Replacer::execute()
{
    char ch;
    std::string buffer = "";

    while ((*fin).get(ch))
    {
        // std::cout << ch << std::endl;
        // if (ch == '\n')
        // {
        //     break;
        // }

        if (offset == searchStr.length())
        {
            offset = 0;
            buffer = "";
            *fout << replaceStr;
        }

        if (searchStr.length() != 0 && ch == searchStr[offset])
        {
            buffer += ch;
            ++offset;
            continue;
        }


        if (buffer != "")
        {
            *fout << buffer;
            buffer = "";
        }
        *fout << ch;

        offset = 0;
    }

    if (offset != 0)
    {
        *fout << buffer;
    }


}
