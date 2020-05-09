#pragma once

#include "../Dictionary/Dictionary.hpp"
#include <memory>
#include <string>

class CommandLineController
{
private:
    std::unique_ptr<Dictionary> dict;

    static const char POSITIVE_ANSWER = 'y';
    const std::string EXIT_SYMBOLS = "...";

    void RunImportDictFromFileScenario();
    void RunAddTranslationToDictScenario(std::string & key, Dictionary::Locale locale);
    void RunSaveChangesScenario();
    void RunUserSession();
    Dictionary::Locale RetrieveLocaleFromUser();
    std::string RetrieveUserInput();

    void PrintUserInvitationHelper();
    void PrintHelp();
    void PrintResults(const std::vector<std::string> & res);
public:
    CommandLineController(std::unique_ptr<Dictionary> d);

    void Start();
};
