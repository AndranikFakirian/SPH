#include <cmath>
#pragma once
double ker(particle p1, particle p2, double h)
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=0.7*M_PI*h*h;
    if (e>=2)
    {
        return 0;
    }
    else if (e<=1)
    {
        return pow(2-e,3)/(4*k);
    }
    else if (e>0)
    {
        return (1-1.5*e*e+0.75*e*e*e)/k;
    }
}
double dker(particle p1, particle p2, double h)
{
    double r=dist(p1, p2);
    double e=r/h;
    double k=2.8*M_PI*h*h*h;
    if (e>=2)
    {
        return 0;
    }
    else if (e<=1)
    {
        return -3*pow(2-e,3)/k;
    }
    else if (e>0)
    {
        return (-12*e+9*e*e)/k;
    }
}
