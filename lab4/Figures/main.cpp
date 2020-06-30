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
#include "Domain/Compound/Compound.hpp"

const int WATER_DENSITY = 1000;

typedef std::vector<std::shared_ptr<Body>> BodiesVector;

void PringBigMassBody(BodiesVector&);
void PrintMinWeightInWaterBody(BodiesVector&);


int main(int argc, char const *argv[])
{
    auto compound1 = std::make_shared<Compound>();

    auto sphere = std::make_shared<Sphere>(3, 4, 4);
    auto sphere_2 = std::make_shared<Sphere>(3, 4, 1);
    auto sphere_3 = std::make_shared<Sphere>(3, 4, 2);

    compound1->AddBody(sphere);
    compound1->AddBody(sphere_3);

    auto compound2 = std::make_shared<Compound>();
    auto compound3 = std::make_shared<Compound>();

    compound1->AddBody(compound2);

    compound2->AddBody(sphere_2);
    compound2->AddBody(compound3);
    // compound3->AddBody(compound1);


    std::cout << "Delete" << std::endl;

    return 0;
}


// int main(int argc, char const *argv[])
// {
//     auto sphere = std::make_shared<Sphere>(3, 4, 4);
//     Cone cone = {3, 4, 1, 4};
//     Cylinder cylinder = {3, 4, 1, 4};
//     Parallelepiped parallelepiped = {1, 4, 5, 6, 7};

//     BodiesVector bodies;

//     bodies.push_back(sphere);

//     PringBigMassBody(bodies);
//     PrintMinWeightInWaterBody(bodies);

//     return 0;
// }

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
