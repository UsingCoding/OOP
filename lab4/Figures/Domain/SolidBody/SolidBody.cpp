#include "SolidBody.hpp"

double SolidBody::GetDensity() const
{
    return density;
}

double SolidBody::GetVolume() const
{
    return volume;
}

double SolidBody::GetMass() const
{
    return density * volume;
}
