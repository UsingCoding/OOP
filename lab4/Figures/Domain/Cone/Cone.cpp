#include "Cone.hpp"
#include "../../../../Utils/StringUtils.hpp"

double Cone::GetHeight() const
{
    return height;
}

Cone::operator std::string() const
{
    return StringUtils::StringConcatenator() << density <<  ' ' << volume << ' ' << GetMass() << ' ' << height;
}
