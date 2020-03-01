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
    std::string line;

    while ((*fin).get(ch))
    {
        if (offset == searchStr.length() && searchStr.length() != 0)
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

        if (searchStr.length() != 0 && ch == searchStr[0])
        {
            *fout << buffer;
            buffer = ch;
            offset = 1;
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

void Replacer::executeSecondV()
{
    std::string buffer = "";
    std::string line;
    std::string resLine = "";

    while (!(*fin).eof())
    {
        getline(*fin, line);

        if (line.length() == 0)
        {
            continue;
        }


        for (size_t i = 0; i < line.length(); i++)
        {
            if (offset == searchStr.length() && searchStr.length() != 0)
            {
                offset = 0;
                buffer = "";
                resLine += replaceStr;
            }

            if (searchStr.length() != 0 && line[i] == searchStr[offset])
            {
                buffer += line[i];
                ++offset;
                continue;
            }

            if (searchStr.length() != 0 && line[i] == searchStr[0])
            {
                resLine += buffer;
                buffer = line[i];
                offset = 1;
                continue;
            }

            if (buffer != "")
            {
                resLine += buffer;
                buffer = "";
            }
            resLine += line[i];

            offset = 0;
        }

        if (buffer != "" && buffer != searchStr)
        {
            resLine += buffer;
            buffer = "";
        }

        *fout << resLine << std::endl;
        resLine = "";
    }
}
