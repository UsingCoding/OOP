#include <iostream>
#include "./Lexer/Lexer.hpp"
#include "./Syntaxer/Syntaxer.hpp"
#include <sstream>
#include <vector>
#include <memory>
#include "./Domain/ResourceManger/ResourceManager.hpp"
#include "./Domain/ArithmeticObjects/Variable.hpp"

int main(int argc, char const *argv[])
{
    // std::istringstream ss("fn abs = trip +wert");
    // std::istringstream ss("var newVar");
    // std::istringstream ss("let newVar = 1 +99");
    // std::istringstream ss("let newVar = 44");

    std::unique_ptr<ResourceManager> manager = std::make_unique<ResourceManager>();

    Syntaxer syntaxer(manager);

    std::string userIn;
    std::vector<std::string> res;

    while (getline(std::cin, userIn))
    {
        res = Lexer::RetrieveTokensList(userIn);

        try
        {
            syntaxer.MapTokensIntoModels(res);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        std::unique_ptr<Variable> var;

        try
        {
            manager->RetrieveVariableByIdentificator("char");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
   

    return 0;
}
