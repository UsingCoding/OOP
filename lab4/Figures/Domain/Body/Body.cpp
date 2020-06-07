#include "Body.hpp"

double Body::GetDensity() const
{
    return density;
}

double Body::GetVolume() const
{
    return volume;
}

double Body::GetMass() const
{
    return density * volume;
}
