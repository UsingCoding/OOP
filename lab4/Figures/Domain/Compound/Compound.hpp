#pragma once

#include "../Body/Body.hpp"
#include <memory>
#include <vector>
#include <functional>

class Compound: public Body
{
private:
    typedef std::shared_ptr<Body> body;

    std::vector<body> bodies;
    std::shared_ptr<Compound> parentBody = nullptr;

    double GetFromAll(std::function<double(body)> getter) const;

    bool CheckForPresence(body body);
public:
    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    operator std::string() const override;
    void AddBody(body body);
};
