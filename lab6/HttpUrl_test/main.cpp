#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include <string>

#include "../HttpUrl/HttpUrl/HttpUrl.hpp"
#include "../../Utils/StringUtils.hpp"

HttpUrl CreateHttpUrl(const std::string & input)
{
    return HttpUrl(input);
}

SCENARIO("Reading url from input string")
{
    GIVEN("String with correct url")
    {
        std::string input("https://some-domain/image.jpg");

        WHEN("We create HttpUrl")
        {
            THEN("We have no erors")
            {
                REQUIRE_NOTHROW(CreateHttpUrl(input));
            }
        }
    }

    GIVEN("String with incorrect url")
    {
        std::string input("htt://some-domain/image.jpg");

        WHEN("We create HttpUrl")
        {
            THEN("We have erors")
            {
                REQUIRE_THROWS(CreateHttpUrl(input));
            }
        }
    }
}

SCENARIO("Creating HttpUrl via params providing")
{
    GIVEN("Required Url params")
    {
        std::string domain("my-site");
        std::string document("main/image.png");

        WHEN("We creating HttpUrl without passing port and protocol")
        {
            THEN("We have no errors")
            {
                REQUIRE_NOTHROW(HttpUrl(domain, document));
            }

            auto httpUrl = HttpUrl(domain, document);

            AND_WHEN("We getting document and protocol")
            {
                THEN("It returns doc with slash and http protocol")
                {
                    REQUIRE(httpUrl.GetDocument() == "/" + document);
                    REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
                    REQUIRE(httpUrl.GetPort() == 80);
                }
            }
        }

        WHEN("Creating HttpUrl with passing protocol and port, and document started with slash")
        {
            std::string slashedDocument("/" + document);

            THEN("We gave no errors")
            {
                REQUIRE_NOTHROW(HttpUrl(domain, slashedDocument, HttpUrl::Protocol::HTTP, 20));
            }

            auto httpUrl = HttpUrl(domain, slashedDocument, HttpUrl::Protocol::HTTP, 20);

            AND_WHEN("We getting document and port")
            {
                REQUIRE(httpUrl.GetDocument() == slashedDocument);
                REQUIRE(httpUrl.GetPort() == 20);
            }
        }
    }
}
