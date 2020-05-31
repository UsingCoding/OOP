#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <sstream>

#include "../CMyString/MyString/MyString.hpp"

SCENARIO("Creating new MyString from diffent type strings")
{
    bool wasError = false;

    WHEN("We create MyString from literal")
    {
        try
        {
            MyString string = "string";
        }
        catch(const std::exception& e)
        {
            true;
        }

        REQUIRE_FALSE(wasError);
    }

    WHEN("We create MyString from std::string")
    {
        try
        {
            std::string str = "string";
            MyString string = str;
        }
        catch(const std::exception& e)
        {
            true;
        }

        REQUIRE_FALSE(wasError);
    }

    WHEN("We create MyString from literal nad lenght")
    {
        try
        {
            MyString string("char", 4);
        }
        catch(const std::exception& e)
        {
            true;
        }

        REQUIRE_FALSE(wasError);
    }
}


SCENARIO("MyString operators")
{
    GIVEN("MyString created from literal with some text")
    {
        MyString string = "tests it`s cool";

        WHEN("We can get 'raw' string")
        {
            REQUIRE(strcmp(string.GetStringData(), "tests it`s cool\0") == 0);
        }

        WHEN("We getting substr from MyString")
        {
            MyString newStr = string.SubString(0, 3);

            THEN("We got new MyString containing substr")
            {
                std::cout << "QWE " <<  newStr.GetStringData() << std::endl;
                REQUIRE(newStr.GetStringData() == "test");
            }
        }

        WHEN("We clear MyString")
        {
            string.Clear();

            THEN("MyString size is 0 and raw data is equal empty string")
            {
                REQUIRE(string.GetLength() == 0);
                REQUIRE(strcmp(string.GetStringData(), "") == 0);
            }
        }

        WHEN("We concate MyString with MyString")
        {
            MyString anotherString = " is true";

            MyString str = string + anotherString;

            THEN("We got new MyString")
            {
                REQUIRE(strcmp(str.GetStringData(), "tests it`s cool is true") == 0);
            }
        }

        WHEN("We concate MySting with std::string")
        {
            std::string anotherString = " is true";

            MyString str = string + anotherString;

            THEN("We got new MyString")
            {
                REQUIRE(strcmp(str.GetStringData(), "tests it`s cool is true") == 0);
            }
        }

        WHEN("We concate MySting with string literal")
        {
            MyString str = string + " is true";

            THEN("We got new MyString")
            {
                REQUIRE(strcmp(str.GetStringData(), "tests it`s cool is true") == 0);
            }
        }

        WHEN("We compare two equal MyString")
        {
            MyString anotherString = "tests it`s cool";

            THEN("We got true")
            {
                REQUIRE(string == anotherString);
            }
        }

        WHEN("We compare as who is bigger")
        {
            MyString anotherString = "tests it`s cool is true";

            THEN("We got that anotherString bigger")
            {
                REQUIRE(string < anotherString);
            }
        }

        WHEN("We compare as who is equal or bigger")
        {
            MyString anotherString = "tests it`s cool";

            THEN("We got true")
            {
                REQUIRE(string <= anotherString);
            }
        }

        WHEN("We try to get some symbol from string by index that more than lenght")
        {
            THEN("We got error")
            {
                bool wasError = false;

                try
                {
                    string[string.GetLength() + 4];
                    wasError = false;
                }
                catch(const std::exception& e)
                {
                    wasError = true;
                }

                REQUIRE(wasError);
            }
        }

        GIVEN("Not empty stream")
        {
            std::istringstream in("Empty \n stream");

            WHEN("We try to read info from this stream")
            {
                MyString str;
                in >> str;

                THEN("We got first word")
                {
                    REQUIRE(str == MyString("Empty"));
                }
            }
        }

        GIVEN("Outstream and MyString")
        {
            std::ostringstream out;
            MyString str = "Info";

            WHEN("We write MyString to outstream")
            {
                out << str;
                THEN("We put this data into stream to the null-terminator")
                {
                    REQUIRE(out.str() == "Info");
                }
            }
        }

        WHEN("We iterate string and put each symbol to other string")
        {
            MyString otherString;

            for (auto &&ch : string)
            {
                otherString += ch;
            }

            THEN("We got equal strings")
            {
                string == otherString;
            }
        }
    }
}
