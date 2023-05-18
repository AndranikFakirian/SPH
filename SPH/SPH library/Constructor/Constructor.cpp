#pragma once
#include "Additional functions/randomizer.cpp"
#include "../Classes&Structures/Particles.hpp"
#include "../Visualizer/Environment Parameters.cpp"
#include "../Solver/SPHfunc.cpp"
Particles::Particles(string c, double x, double y, double vx, double vy, double m, long int Num, double h): h(h)
{
    for (long i=0; i<Num; i++)
    {
        //Defining 0 positions
    }
    double ro0=0;
    for (long i=0; i<Num; i++)
    {
        ro0+=ro(p, i, h);
    }
    ro0=ro0/Num;
    for (long i=0; i<Num; i++)
    {
        p[i].ro0=ro0;
    }
    for (long i=0; i<Num; i++)
    {
        //Randomizing 0 positions
    }
}
