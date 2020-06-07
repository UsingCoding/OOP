#include "Sphere.hpp"
#include "../../../../Utils/StringUtils.hpp"

Sphere::operator std::string() const
{
    return StringUtils::StringConcatenator() << density <<  ' ' << volume << ' ' << GetMass() << ' ' << radius;
}
