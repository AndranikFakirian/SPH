#pragma once
#include "particle.cpp"
#include <vector>
class Particles
{
public:
    vector <particle> p;
    static long int N;
    static double h;
    Particles (string c, double x, double y, double vx, double vy, double m, long int Num, double h);
};
long int Particles::N=0;
double Particles::h=0;
