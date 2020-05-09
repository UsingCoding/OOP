#include "./Decode.hpp"
#include <iostream>

std::string HtmlDecode(const std::string &html)
{
    bool htmlEntityStarted = false;
    std::string resLine;
    int offset = -1;

    for (size_t i = 0; i < html.length(); i++)
    {
        if (html[i] == HTML_ENTITY_BEGINS)
        {
            htmlEntityStarted = true;

            if (offset != -1)resLine += html.substr(offset, i - offset);

            offset = i;
            continue;
        }

        if (html[i] == HTML_ENTITY_ENDS && htmlEntityStarted)
        {
            std::string checkHtmlEntity = html.substr(offset + 1, i - offset - 1);
            htmlEntityStarted = false;
            offset = -1;
            auto it = htmlEntitiesMap.find(checkHtmlEntity);
            if (it != htmlEntitiesMap.end())
            {
                resLine += it->second;
            }
            else
            {
                resLine += HTML_ENTITY_BEGINS + checkHtmlEntity + HTML_ENTITY_ENDS;
            }

            continue;
        }

        if (htmlEntityStarted)
        {
            continue;
        }

        resLine += html[i];
    }

    if (offset != -1)
    {
        resLine += html.substr(offset, html.length() - offset);
    }

    return resLine;
}
