#include "Parallelepiped.hpp"
#include "../../../../Utils/StringUtils.hpp"

double Parallelepiped::GetHeight() const
{
    return height;
}
double Parallelepiped::GetWidht() const
{
    return width;
}
double Parallelepiped::GetDepth() const
{
    return depth;
}
Parallelepiped::operator std::string() const
{
    return StringUtils::StringConcatenator() << density <<  ' ' << volume << ' ' << GetMass() << height << ' ' << width << ' ' << depth;
}
