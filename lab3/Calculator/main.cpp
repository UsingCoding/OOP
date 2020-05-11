#include <iostream>
#include "./Lexer/Lexer.hpp"
#include "./Syntaxer/Syntaxer.hpp"
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
    // std::istringstream ss("fn abs = trip +wert");
    // std::istringstream ss("var newVar");
    std::istringstream ss("let newVar = 1 +99");
    // std::istringstream ss("let newVar = 44");


    std::vector<std::string> res = Lexer::RetrieveTokensList(ss);

    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << std::endl;
    }

    try
    {
        Syntaxer::MapTokensIntoModels(res);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}
