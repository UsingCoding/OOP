#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

#include "../HtmlDecode/Decode.hpp"

SCENARIO("Decode empty string")
{
    REQUIRE(HtmlDecode("") == "");
}

SCENARIO("Decode string with symbols but not html entities")
{
    REQUIRE(HtmlDecode("Cat ") == "Cat ");
}

SCENARIO("Decode string contains only HTML entity")
{
    REQUIRE(HtmlDecode("&lt;") == "<");
}

SCENARIO("Decode string contains not full HTML entity")
{
    REQUIRE(HtmlDecode("&lt") == "&lt");
}

SCENARIO("Decode string contains multiply HTML entityies divided by space")
{
    REQUIRE(HtmlDecode("&lt; &gt;") == "< >");
}

SCENARIO("Decode string with HTML special characters")
{
    REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M`s");
}

