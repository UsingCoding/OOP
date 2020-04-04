#include <iostream>
#include "./Dictionary/Dictionary.hpp"

int main(int argc, char const *argv[])
{
    Dictionary dictionary;

    std::string firstWord;

    dictionary.addTranslation("Cat", "Кошка", Dictionary::EN);

    try
    {
        dictionary.retrieveTranslation("CAT", Dictionary::EN);
    }
    catch(const DictionaryException& e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}
