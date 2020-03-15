#include "ReplaceInStream.hpp"

void ReplaceInStream::Execute(std::istream * in, std::ostream * out, std::string searchStr, std::string replaceStr)
{
    int offset = 0;
    std::string buffer;
    std::string line;
    std::string resLine;

    while (!(*in).eof())
    {

        getline(*in, line);

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

        *out << resLine << std::endl;
        resLine = "";
    }
}
