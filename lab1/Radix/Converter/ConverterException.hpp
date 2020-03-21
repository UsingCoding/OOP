#include <exception>
#include <stdexcept>

class ConverterException: std::exception
{
private:
    std::string msg;
public:
    ConverterException(std::string msg);
    const std::string getMsg() const noexcept;
    void setMsg(const std::string & msg);

    static ConverterException convertOverflowError();
};
