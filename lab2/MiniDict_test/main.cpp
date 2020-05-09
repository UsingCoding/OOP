#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>
#include <fstream>

#include "../MiniDict/Dictionary/Dictionary.hpp"

typedef std::vector<std::string> DictionaryResponse;

SCENARIO("Retrieving translation from empty dict")
{
    GIVEN("Empty dictionary")
    {
        Dictionary dict;

        WHEN("We try to retrieve translation")
        {
            std::string key = "key";
            Dictionary::Locale locale = Dictionary::Locale::EN;

            DictionaryResponse res = dict.RetrieveTranslation(key, locale);

            THEN("Response from dict is empty")
            {
                REQUIRE(res == DictionaryResponse{});
            }
        }
    }
}

SCENARIO("Retrieving word from different case")
{
    Dictionary dict;

    std::string key = "key";
    std::string translate = "Ключ";
    Dictionary::Locale locale = Dictionary::Locale::RU;

    dict.AddTranslation(key, translate, locale);

    std::string keyInUpper = "KEY";

    DictionaryResponse res = dict.RetrieveTranslation(keyInUpper, locale);

    REQUIRE(res.size() != 0);
    REQUIRE(res[0] == translate);
}

SCENARIO("Add word with double translation and retrieving it")
{
    GIVEN("Empty dictionary and word with two key translations")
    {
        Dictionary dict;

        std::string firstKey = "cat";
        std::string secondKey = "Catty";
        std::string translate = "Кошка";
        Dictionary::Locale locale = Dictionary::Locale::RU;

        WHEN("We add first translation")
        {
            std::string cpTranslation = translate;
            dict.AddTranslation(firstKey, cpTranslation, locale);
            
            THEN("Response from dict on current translation is one word")
            {
                locale = Dictionary::Locale::EN;
                cpTranslation = translate;
                DictionaryResponse res = dict.RetrieveTranslation(translate, locale);
                REQUIRE(res.size() == 1);
                REQUIRE(res[0] == firstKey);
            }

            AND_WHEN("Add second translation")
            {
                dict.AddTranslation(secondKey, translate, locale);

                THEN("Response from dict on current translation is two words")
                {
                    locale = Dictionary::Locale::EN;
                    DictionaryResponse res = dict.RetrieveTranslation(translate, locale);
                    REQUIRE(res.size() == 2);
                }
            }
        }
    }
}

SCENARIO("You can try to retrieve unexisting translation")
{
    GIVEN("Empty dict")
    {
        Dictionary dict;

        WHEN("We added some translation into dict")
        {
            std::string newKey = "key";
            std::string translation = "Ключик";
            Dictionary::Locale locale = Dictionary::Locale::RU;

            dict.AddTranslation(newKey, translation, locale);

            AND_WHEN("We retrieving unexisting translation")
            {
                std::string unexistingKey = "?!?!?!@";
                DictionaryResponse res = dict.RetrieveTranslation(unexistingKey, locale);

                THEN("Answer from dict is empty vector")
                {
                    REQUIRE(res.size() == 0);
                }
            }
        }
    }
}

SCENARIO("Translation case didn`t lose and dict translate in two way(back and forth)")
{
    GIVEN("Empty dict")
    {
        Dictionary dict;

        WHEN("We add translation in some case")
        {
            std::string key = "key";
            std::string translation = "CaMeLcAsE";
            Dictionary::Locale locale = Dictionary::Locale::EN;

            std::string cpTranslation = translation;
            dict.AddTranslation(key, cpTranslation, locale);

            AND_WHEN("We retrieve this tranlation")
            {
                DictionaryResponse res = dict.RetrieveTranslation(key, locale);

                THEN("Translation case didn`t change")
                {
                    REQUIRE(res[0] == translation);
                }
            }
        }

        WHEN("We add some translation")
        {
            std::string key = "key";
            std::string translation = "Ключи";
            Dictionary::Locale locale = Dictionary::Locale::RU;

            dict.AddTranslation(key, translation, locale);

            AND_WHEN("We retrieving translation via translated word")
            {
                locale = Dictionary::Locale::EN;
                DictionaryResponse res = dict.RetrieveTranslation(translation, locale);

                THEN("Response is one key word")
                {
                    REQUIRE(res[0] == key);
                }
            }
        }
    }
}

SCENARIO("Dictionary can be serialized and unserialized")
{
    GIVEN("Dictionary with two translations")
    {
        Dictionary dict;

        {
            std::string firstKey = "Cat";
            std::string firstTranslation = "Кошка";
            Dictionary::Locale firstLocale = Dictionary::Locale::RU;

            std::string secondKey = "Самолёт";
            std::string secondTranslation = "JET";
            Dictionary::Locale secondLocale = Dictionary::Locale::EN;

            dict.AddTranslation(firstKey, firstTranslation, firstLocale);
            dict.AddTranslation(secondKey, secondTranslation, secondLocale);
        }

        WHEN("We serialize dict")
        {
            std::string res = dict.Serialize();

            THEN("We got a dict version to save somewhere in file")
            {
                std::ofstream fout("ex.yml");
                fout << res;
            }
        }
    }

    GIVEN("Empty dict")
    {
        Dictionary dict;

        WHEN("We unserialize dict from file")
        {
            std::ifstream fin("ex.yml");
            if (!fin.is_open())
            {
                std::cout << "Failed to open test file" << std::endl;
                return;
            }
            
            try
            {
                dict.Unserialize(fin);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            THEN("We can retrieve translations from dict")
            {
                std::string key = "Cat";
                Dictionary::Locale locale = Dictionary::Locale::RU;
                DictionaryResponse res = dict.RetrieveTranslation(key, locale);

                REQUIRE(res[0] == "Кошка");
            }
            
        }
    }
}

