#include <exception>
#include <stdexcept>

class ConverterException: std::exception
{
private:
    std::string msg;
public:
    ConverterException(std::string msg);
    std::string getMsg();

    static ConverterException convertOverflowError();
};
