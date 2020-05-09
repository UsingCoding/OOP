#include "./CommandLineController.hpp"

#include <iostream>
#include <algorithm>
#include <fstream>

#include "../../../Utils/StringUtils.hpp"

const std::string CommandLineController::EXIT_SYMBOLS = "...";

CommandLineController::CommandLineController(std::unique_ptr<Dictionary> d)
{
    dict = std::move(d);
}

void CommandLineController::PrintHelp()
{
    std::cout << "Пример:" << std::endl;
    std::string exWord = "Alone";
    std::cout << ">> " << exWord << std::endl;
    std::cout << "Неизвестное слово " << exWord << ". Введите перевод или пустую строку для отказа." << std::endl;
    std::string exTranslate = "Одинокий";
    std::cout << ">> " << exTranslate << std::endl;
    std::cout << "Принято, введите локаль перевода" << std::endl;
    std::cout << ">> Ru" << std::endl;
    std::cout << "Слово " << exWord << " сохранено в словаре как " << exTranslate << "." << std::endl;
}

void CommandLineController::PrintResults(const std::vector<std::string> & res)
{
    for (size_t i = 0; i < res.size(); i++)
    {
        if (i != 0) std::cout << ", ";
        
        std::cout << res[i];
    }

    std::cout << std::endl;
}

std::string CommandLineController::RetrieveUserInput()
{
    std::string res;
    while (true)
    {
        std::cout << ">> ";
        getline(std::cin, res);
        if (StringUtils::Trim(res).length() != 0)
        {
            break;
        }
        
        std::cout << "Введите строку содержащее что-то помимо пробелов" << std::endl;
    }
    
    return res;
}

void CommandLineController::Start()
{
    std::cout << "Доброе время суток, чтобы начать работу со словарём вы можете указать из какого файла импортировать данные" << std::endl;
    std::cout << "Хотите импортировать данные? [Y/y]" << std::endl;
    
    std::string userIn = RetrieveUserInput();

    std::transform(userIn.begin(), userIn.begin(), userIn.end(), tolower);

    if(userIn[0] == POSITIVE_ANSWER)
    {
        RunImportDictFromFileScenario();
    }
    else
    {
        std::cout << "Продолжим без инициализации" << std::endl;
    }
    
    RunUserSession();
}

void CommandLineController::RunUserSession()
{
    std::cout << "Введите слово, которое вы хотите перевести, если его нет в словаре, то можно ввести перевод, чтобы его запомнить, в обоих случаях нужно указать локаль перевода" << std::endl;
    PrintHelp();
    std::cout << std::endl << "Чтобы закончить работу со словарём введите \"...\"" << std::endl;

    std::string userIn;
    std::string key;
    Dictionary::Locale locale;

    while (true)
    {
        std::cout << "Введите слово...." << std::endl;
        key = RetrieveUserInput();

        if (key == EXIT_SYMBOLS)
        {
            break;
        }

        std::cout << "Пожалуйста, введите локаль перевода" << std::endl;

        locale = RetrieveLocaleFromUser();

        std::vector<std::string> res = dict->RetrieveTranslation(key, locale);

        if (res.size() != 0)
        {
            PrintResults(res); 
            continue;
        }
        
        RunAddTranslationToDictScenario(key, locale);
    }

    RunSaveChangesScenario();

    std::cout << "До свидания" << std::endl;
}

Dictionary::Locale CommandLineController::RetrieveLocaleFromUser()
{
    std::string userIn;

    while (true)
    {
        userIn = RetrieveUserInput();

        try
        {
            return dict->RetrieveLocaleFromString(userIn);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "Попробуйте ещё раз" << std::endl;
        }
    }
}

void CommandLineController::RunImportDictFromFileScenario()
{
    std::cout <<  "Введите название файла. Программа экспортирует данные из похожего на YAML формата, введите \"" << EXIT_SYMBOLS << "\" для пропуска этого шага." << std::endl;

    std::string userIn;
    std::ifstream fin;

    while (true)
    {
        userIn = RetrieveUserInput();

        if (userIn == EXIT_SYMBOLS)
        {
            std::cout << "Импорт отменён" << std::endl;
            return;
        }
        
        fin.open(userIn);

        if (!fin.is_open())
        {
            std::cout << "Файл не удалось открыть, может попробуете другой?" << std::endl;
            fin.close();
            continue;
        }

        try
        {
            dict->Unserialize(fin);
        }
        catch(const std::exception& e)
        {
            std::cout << "Неудалось десериализовать из файла: " << e.what() << std::endl << "Может попробуйте другой файл?" << std::endl;
            continue;
        }

        break;
    }

    std::cout << "Данные успешно импортированы" << std::endl;
}

void CommandLineController::RunAddTranslationToDictScenario(std::string & key, Dictionary::Locale locale)
{
    std::cout << "Неизвестное слово \"" << key << "\". Введите перевод или " << EXIT_SYMBOLS << " для отказа" << std::endl;
    std::string userIn = RetrieveUserInput();

    if (StringUtils::StartsWith(userIn, EXIT_SYMBOLS))
    {
        std::cout << "Слово \"" << key << "\" проигнорировано" << std::endl;
        return;
    }

    dict->AddTranslation(key, userIn, locale);

    std::cout << "Слово \"" << key << "\" сохранено в словаре как \"" << userIn << "\"." << std::endl;
}

void CommandLineController::RunSaveChangesScenario()
{
    std::cout << "В словарь были внесены изменения. Введите [Y/n] для сохранения перед выходом." << std::endl;

    std::string userIn = RetrieveUserInput();
    std::transform(userIn.begin(), userIn.begin(), userIn.end(), tolower);

    if (userIn[0] == POSITIVE_ANSWER)
    {
        while (true)
        {
            std::cout << "Введите название файла для сохранения или \"" << EXIT_SYMBOLS << "\" для отмены" << std::endl;
            userIn = RetrieveUserInput();

            if (userIn == EXIT_SYMBOLS)
            {
                break;
            }

            std::ofstream fout(userIn);
            if (!fout.is_open())
            {
                std::cout << "Не получилось открыть файл, может попробуйте другой?" << std::endl;
                continue;
            }

            fout << dict->Serialize();

            std::cout << "Данные успешно сохранены" << std::endl;
            break;
        }
    }

    std::cout << "Сохранение отменено" << std::endl;
}