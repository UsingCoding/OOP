#include <iostream>
#include "./Dictionary/Dictionary.hpp"

#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
    Dictionary dictionary;

    std::string firstWord;

    std::string original = "Cat";
    std::string translate = "Кошка";

    dictionary.AddTranslation(original, translate, Dictionary::RU);

    original = "Jet";
    translate = "Самолёт";

    dictionary.AddTranslation(original, translate, Dictionary::RU);

    std::cout << dictionary.Serialize() << std::endl;


    return 0;
}
