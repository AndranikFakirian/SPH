#pragma once
#include "../Classes&Structures/particle.cpp"
#include "Liquid.cpp"
#include "Additional functions/scalar.cpp"

double Liquid::dro(unsigned int ind)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        if (ind!=i)
        {
            val+=(liq[i].m*liq[ind].ro*DK[ind][i]/liq[i]*scalar(liq[ind].vx-liq[i].vx, liq[ind].vy-liq[i].vy, liq[ind].x-liq[i].x, liq[ind].y-liq[i].y)/dist(liq[ind], liq[i]));
        }
    }
    return -1*val;
}
double Liquid::dE(unsigned int ind)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        if (ind!=i)
        {
            val+=(liq[i].m*(liq[i].p+liq[ind].p)*DK[ind][i]/2/liq[i].ro/liq[ind].ro*scalar(liq[ind].vx-liq[i].vx, liq[ind].vy-liq[i].vy, liq[ind].x-liq[i].x, liq[ind].y-liq[i].y)/dist(liq[ind], liq[i]));
        }
    }
    return -1*val;
}
double Liquid::dVx(unsigned int ind)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        if (ind!=i)
        {
            val+=(liq[i].m*(liq[i].p+liq[ind].p)*DK[ind][i]/liq[i].ro/liq[ind].ro*(liq[ind].x-liq[i].x)/dist(liq[ind], liq[i]));
        }
    }
    return val;
}
double Liquid::dVy(unsigned int ind)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        if (ind!=i)
        {
            val+=(liq[i].m*(liq[i].p+liq[ind].p)*DK[ind][i]/liq[i].ro/liq[ind].ro*(liq[ind].y-liq[i].y)/dist(liq[ind], liq[i]));
        }
    }
    return val;
}
double ro(vector <particle> liq, unsigned int ind, double h) //Speed - O(n)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        val+=(liq[i].m*ker(liq[ind],liq[i], h));
    }
    return val;
}
