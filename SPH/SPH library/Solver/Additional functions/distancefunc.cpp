#pragma once
#include "distancefunc.hpp"
#include <cmath>
double dist(particle p1, particle p2)
{
    double dr=std::pow(p1.x-p2.x, 2)+std::pow(p1.y-p2.y, 2);
    return pow(dr,0.5);
}
