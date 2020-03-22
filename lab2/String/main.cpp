#include <iostream>
#include <map>

const char HTML_ENTITY_BEGINS = '&';
const char HTML_ENTITY_ENDS = ';';

const std::string DOUBLE_QUOTE = "quot";
const std::string APOSTROPHE = "apos";
const std::string MARK_LESS = "lt";
const std::string MARK_GREATER = "gt";
const std::string AMPERSAND = "amp";

std::map<std::string, char> htmlEntitiesMap = {
    { DOUBLE_QUOTE, '"' },
    { APOSTROPHE, '`' },
    { MARK_LESS, '<' },
    { MARK_GREATER, '>' },
    { AMPERSAND, '&' }
};

std::string HtmlDecode(const std::string &html);

int main(int argc, char const *argv[])
{
    std::string line;
    while (getline(std::cin, line))
    {
        std::cout << HtmlDecode(line) << std::endl;
    }

    return 0;
}

std::string HtmlDecode(const std::string &html)
{
    bool htmlEntityStarted = false;
    std::string resLine;
    std::string currEntity;
    std::string buffer;
    int offset = 0;

    for (size_t i = 0; i < html.length(); i++)
    {
        if (html[i] == HTML_ENTITY_BEGINS && !htmlEntityStarted)
        {
            htmlEntityStarted = true;
            continue;
        }

        if (html[i] == HTML_ENTITY_ENDS && htmlEntityStarted)
        {
            htmlEntityStarted = false;
            resLine += htmlEntitiesMap[currEntity];
            offset = 0;
            buffer = "";
            continue;
        }

        if (htmlEntityStarted)
        {
            buffer += html[i];

            if (html[i] == DOUBLE_QUOTE[offset])
            {
                ++offset;
                currEntity = DOUBLE_QUOTE;
                continue;
            }

            if (html[i] == APOSTROPHE[offset])
            {
                ++offset;
                currEntity = APOSTROPHE;
                continue;
            }

            if (html[i] == MARK_LESS[offset])
            {
                ++offset;
                currEntity = MARK_LESS;
                continue;
            }

            if (html[i] == MARK_GREATER[offset])
            {
                ++offset;
                currEntity = MARK_GREATER;
                continue;
            }

            if (html[i] == AMPERSAND[offset])
            {
                ++offset;
                currEntity = AMPERSAND;
                continue;
            }
        }

        resLine += html[i];
    }

    if (buffer != "")
    {
        resLine += buffer;
    }


    return resLine;
}
