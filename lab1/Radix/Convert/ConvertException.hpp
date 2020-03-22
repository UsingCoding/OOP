#include <exception>
#include <stdexcept>

class ConvertException: std::exception
{
private:
    std::string msg;
public:
    ConvertException(std::string msg);
    const std::string getMsg() const noexcept;
    void setMsg(const std::string & msg);

    static ConvertException convertOverflowError();
};
