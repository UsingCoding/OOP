#include <iostream>
#include <fstream>

bool OpenFiles(std::ifstream & fin, std::ofstream & fout, std::string firstFileName, std::string secondFileName);
void ReplaceInStream(std::istream & in, std::ostream & out, const std::string & searchStr, const std::string & replaceStr);

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        std::cout << "Incorrect count of arguments" << std::endl;
        return 1;
    }

    std::ifstream fin;
    std::ofstream fout;

    if (!OpenFiles(fin,  fout, argv[1], argv[2]))
    {
        return 1;
    }

    ReplaceInStream(fin, fout, argv[3], argv[4]);

    return 0;
}

bool OpenFiles(std::ifstream & fin, std::ofstream & fout, std::string firstFileName, std::string secondFileName)
{
    fin.open(firstFileName);
    fout.open(secondFileName);

    return fin.is_open() && fout.is_open();
}

void ReplaceInStream(std::istream & in, std::ostream & out, const std::string & searchStr, const std::string & replaceStr)
{
    int offset = 0;
    std::string buffer;
    std::string line;
    std::string resLine;

    while (!in.eof())
    {
        getline(in, line);

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

        out << resLine << std::endl;
        resLine = "";
    }
}
