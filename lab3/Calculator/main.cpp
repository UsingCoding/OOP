#include <iostream>
#include "./Lexer/Lexer.hpp"
#include "./Syntaxer/Syntaxer.hpp"
#include "./NodeBuilder/NodeBuilder.hpp"
#include "./NodeBuilder/NodeBuilderInput.hpp"
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
    std::unique_ptr<NodeBuilder> nodeBuilder = std::make_unique<NodeBuilder>(manager);


    std::string userIn;
    std::vector<std::string> res;
    std::unique_ptr<NodeBuilderInput> input;

    while (getline(std::cin, userIn))
    {
        res = Lexer::RetrieveTokensList(userIn);
        try
        {
            input = Syntaxer::ParseTokens(res);
            nodeBuilder->MapIntoModels(*input);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
    }
   

    return 0;
}
