#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include "Liquid.cpp"
#include "Additional functions/scalar.cpp"
#include <cmath>
#include <iterator>

double Liquid::derRo(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*liq[ind].ro*ppai->dk/ppai->pparticle.ro*scalar(liq[ind].vx-ppai->pparticle.vx, liq[ind].vy-ppai->pparticle.vy, liq[ind].x-ppai->pparticle.x, liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return -1*val;
}
double Liquid::derE(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/2/ppai->pparticle.ro/liq[ind].ro*scalar(liq[ind].vx-ppai->pparticle.vx, liq[ind].vy-ppai->pparticle.vy, liq[ind].x-ppai->pparticle.x, liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return -1*val;
}
double Liquid::derVx(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/ppai->pparticle.ro/liq[ind].ro*(liq[ind].x-ppai->pparticle.x)/dist(liq[ind], ppai->pparticle));
    }
    return val;
}
double Liquid::derVy(unsigned int ind) //Speed - O(1)
{
    double val=0;
    for (std::vector <ppair>::iterator ppai=DK[ind].begin(); ppai!=DK[ind].end(); ++ppai)
    {
        val+=(ppai->pparticle.m*(ppai->pparticle.p+liq[ind].p)*ppai->dk/ppai->pparticle.ro/liq[ind].ro*(liq[ind].y-ppai->pparticle.y)/dist(liq[ind], ppai->pparticle));
    }
    return val;
}
double Liquid::press(unsigned int ind) //Speed - O(1)
{
    return k*(std::pow(liq[ind].ro/liq[ind].ro0, 7)-1);
}
double ro(std::vector <particle> liq, unsigned int ind, double h) //Computing densities of particles //Speed - O(n)
{
    double val=0;
    for (unsigned int i=0; i<liq.size(); i++)
    {
        val+=(liq[i].m*Ker(liq[ind],liq[i], h));
    }
    return val;
}
