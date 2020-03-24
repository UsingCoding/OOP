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
    // std::string line;
    // while (getline(std::cin, line))
    // {
    //     std::cout << HtmlDecode(line) << std::endl;
    // }

    std::cout << HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") << std::endl;

    return 0;
}

std::string HtmlDecode(const std::string &html)
{
    bool htmlEntityStarted = false;
    std::string resLine;
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
            auto it = htmlEntitiesMap.find(buffer);
            if (it != htmlEntitiesMap.end())
            {
                resLine += it->second;
            }
            else
            {
                resLine += HTML_ENTITY_BEGINS + buffer + HTML_ENTITY_ENDS;
            }


            offset = 0;
            buffer = "";
            continue;
        }

        if (htmlEntityStarted)
        {
            buffer += html[i];
            ++offset;
            continue;
        }

        resLine += html[i];
    }

    if (buffer != "")
    {
        resLine += buffer;
    }


    return resLine;
}
