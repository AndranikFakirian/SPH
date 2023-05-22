#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include <iterator>
#include "../Visualizer/Environment_Parameters.cpp"
Liquid::Liquid (vector <Particles>& P, double alpha, double k, double g, double dt): alpha(alpha), k(k), g(g), dt(dt) //Speed - O(N), memory - O(N)
{
    liq.resize(N);
    long pointer=0;
    for (long i=0; i<P.size(); i++)
    {
        for (long j=0; j<P[i].getParticles().size(); j++)
        {
            liq[pointer]=P[i].p[j];
            pointer++;
        }
    }
}
