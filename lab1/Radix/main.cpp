#include <iostream>
#include "./Convert/Convert.hpp"
#include <exception>
#include <stdexcept>

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        std::cout << "Missing arguments, need to pass 3 arguments" << std::endl;
        return 1;
    }

    try
    {
        int srcNot;
        int destNot;

        try
        {
            srcNot = ParseInt(argv[1]);
            destNot = ParseInt(argv[2]);
        }
        catch(ConvertException e)
        {
            e.setMsg("Incorrect symbol in notation");
            throw e;
        }

        if (!(2 <= srcNot && srcNot <= 36) || !(2 <= destNot && destNot <= 36))
        {
            throw ConvertException("Incorrect range of notation");
        }

        std::string value = argv[3];

        bool isNeg = IsNegative(value);
        if (isNeg)
        {
            value.erase(0, 1);
        }

        int intValue = StringToInt(value, srcNot);
        value = IntToString(intValue, destNot);

        std::cout << (!isNeg ? value : "-" + value) << std::endl;
    }
    catch (const ConvertException & e)
    {
        std::cerr << e.getMsg() << std::endl;
        return 1;
    }

    return 0;
}
