#include "Compound.hpp"
#include "../../../../Utils/StringUtils.hpp"

#include <iostream>

double Compound::GetDensity() const
{
    return GetFromAll([](body body) { return body->GetDensity(); });
}

double Compound::GetVolume() const
{
    return GetFromAll([](body body) { return body->GetVolume(); });
}

double Compound::GetMass() const
{
    return GetFromAll([](body body) { return body->GetMass(); });
}

void Compound::AddBody(std::shared_ptr<Body> body)
{
    if (typeid(Compound).hash_code() == typeid(*body).hash_code())
    {
        if (CheckForPresence(body))
        {
            return;
        }

        std::cout << "I don`t know what to say" << std::endl;
        Compound *compound = dynamic_cast<Compound*>(body.get());
        compound->parentBody = std::shared_ptr<Compound>(this);
    }

    bodies.push_back(body);
    std::cout << "Temp crash" << std::endl;
}

Compound::operator std::string() const
{
    return StringUtils::StringConcatenator() << GetDensity() <<  ' ' << GetVolume() << ' ' << GetMass();
}

double Compound::GetFromAll(std::function<double(std::shared_ptr<Body>)> getter) const
{
    double sum;

    for (size_t i = 0; i < bodies.size(); i++)
    {
        sum += getter(bodies[i]);
    }

    return sum;
}

bool Compound::CheckForPresence(body body)
{
    if (parentBody == nullptr)
    {
        return false;
    }

    if (parentBody.get() == body.get())
    {
        return true;
    }

    return parentBody->CheckForPresence(body);
}
