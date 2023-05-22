#pragma once
#include <cmath>
#include "../Classes&Structures/Liquid.hpp"
#include "Additional functions/distancefunc.cpp"
double Ker(particle p1, particle p2, double h)  //Kernel function
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=0.7*M_PI*h*h;
    if ((e>=2)||(e==0))
    {
        return 0;
    }
    else if (e<=1)
    {
        return std::pow(2-e,3)/(4*k);
    }
    else if (e>0)
    {
        return (1-1.5*std::pow(e, 2)+0.75*std::pow(e, 3))/k;
    }
}
double Liquid::DerKer(particle p1, particle p2, double h)
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=2.8*M_PI*h*h*h;
    if ((e>=2)||(e==0))
    {
        return 0;
    }
    else if (e<=1)
    {
        return -3*std::pow(2-e,3)/k;
    }
    else if (e>0)
    {
        return (-12*e+9*std::pow(e, 2))/k;
    }
}
