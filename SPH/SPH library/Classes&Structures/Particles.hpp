#pragma once
#include "particle.cpp"
#include <vector>
class Particles
{
public:
    vector <particle> p;
    Particles (string c, double x, double y, double vx, double vy, double m);
};
