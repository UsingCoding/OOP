#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <float.h>
#include <math.h>
#include <stdexcept>

#include "Domain/Sphere/Sphere.hpp"
#include "Domain/Cone/Cone.hpp"
#include "Domain/Cylinder/Cylinder.hpp"
#include "Domain/Parallelepiped/Parallelepiped.hpp"

const int WATER_DENSITY = 1000;

typedef std::vector<std::shared_ptr<Body>> BodiesVector;

void PringBigMassBody(BodiesVector&);
void PrintMinWeightInWaterBody(BodiesVector&);

int main(int argc, char const *argv[])
{
    auto sphere = std::make_shared<Sphere>(3, 4, 4);
    Cone cone = {3, 4, 1, 4};
    Cylinder cylinder = {3, 4, 1, 4};
    Parallelepiped parallelepiped = {1, 4, 5, 6, 7};

    BodiesVector bodies;

    bodies.push_back(sphere);

    PringBigMassBody(bodies);
    PrintMinWeightInWaterBody(bodies);

    return 0;
}

void PringBigMassBody(BodiesVector & bodies)
{
    std::sort(bodies.begin(), bodies.end(), [](const std::shared_ptr<Body> & body1, const std::shared_ptr<Body> & body2){
        return body1->GetMass() < body2->GetMass();
    });

    std::cout << (std::string) *(bodies[bodies.size() - 1]) << std::endl;
}

void PrintMinWeightInWaterBody(BodiesVector& bodies)
{
    std::sort(bodies.begin(), bodies.end(), [](const std::shared_ptr<Body> & body1, const std::shared_ptr<Body> & body2){
        return body1->GetVolume() < body2->GetVolume();
    });

    std::cout << (std::string) *(bodies[bodies.size() - 1]) << std::endl;
}
