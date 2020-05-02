#include "./Decode.hpp"

std::string HtmlDecode(const std::string &html)
{
    bool htmlEntityStarted = false;
    std::string resLine;
    std::string buffer;

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

            buffer = "";
            continue;
        }

        if (htmlEntityStarted)
        {
            buffer += html[i];
            continue;
        }

        resLine += html[i];
    }

    if (buffer != "")
    {
        resLine += HTML_ENTITY_BEGINS + buffer;
    }


    return resLine;
}
