#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

#include "../UrlParser/Parser/Parser.hpp"

SCENARIO("Parse empty string")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "";

    REQUIRE(ParseURL(url, protocol, port, host, document) == false);
}

SCENARIO("Parse string with basic url")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "https://mysite.com";

    REQUIRE(ParseURL(url, protocol, port, host, document) == true);
    REQUIRE(host == "mysite.com");
    REQUIRE(port == 443);
    REQUIRE(document == "");
}

SCENARIO("Parse string with http, doc and port")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "https://mysite.com:222/assignee.xml";

    REQUIRE(ParseURL(url, protocol, port, host, document) == true);
    REQUIRE(host == "mysite.com");
    REQUIRE(port == 222);
    REQUIRE(document == "assignee.xml");
}

SCENARIO("Parse string with FTP, doc and port")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "ftp://mysite.com/assignee.xml";

    REQUIRE(ParseURL(url, protocol, port, host, document) == true);
    REQUIRE(host == "mysite.com");
    REQUIRE(port == 21);
    REQUIRE(document == "assignee.xml");
}

SCENARIO("Parse string with unknown protocol")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "ftpss://mysite.com/assignee.xml";

    REQUIRE(ParseURL(url, protocol, port, host, document) == false);
}

SCENARIO("Parse string with port 65535 and 1 and between")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url;

    url = "https://mysite.com:65535/assignee.xml";
    REQUIRE(ParseURL(url, protocol, port, host, document) == true);

    url = "https://mysite.com:1/assignee.xml";
    REQUIRE(ParseURL(url, protocol, port, host, document) == true);

    url = "https://mysite.com:768/assignee.xml";
    REQUIRE(ParseURL(url, protocol, port, host, document) == true);
}


SCENARIO("Parse full ready url")
{
    Protocol protocol;
    int port;
    std::string host;
    std::string document;

    std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";

    REQUIRE(ParseURL(url, protocol, port, host, document) == true);
    REQUIRE(host == "www.mysite.com");
    REQUIRE(port == 80);
    REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}
