#include "Cylinder.hpp"
#include "../../../../Utils/StringUtils.hpp"

double Cylinder::GetHeight() const
{
    return height;
}

Cylinder::operator std::string() const
{
    return StringUtils::StringConcatenator() << density <<  ' ' << volume << ' ' << GetMass() << ' ' << height;
}
