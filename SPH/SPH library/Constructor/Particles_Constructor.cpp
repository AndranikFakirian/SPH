#pragma once
#include "Additional functions/randomizer.hpp"
#include "../Visualizer/Environment_Parameters.hpp"
#include "../Solver/Ro.hpp"
#include "../Classes&Structures/Particles.hpp"
#include <cmath>
Particles::Particles(std::string c, double vx, double vy, double m, long int Num, double h) //Speed - O(N), memory - O(N)
{
    this->h=h;
    long tempNum=N+Num;
    long tNum=0;
    if (tempNum>E_p_heigth*E_p_length)
        tNum=E_p_heigth*E_p_length-N;
    else
        tNum=tempNum;
    p.resize(tNum);
    double x0=(E_WX-E_length)/2+1+E_rad;
    double y0=E_height+E_indent-1-E_rad;
    for (long i=0; i<tNum; i++)
    {
        particle pa;
        N++;
        pa.color=c;
        pa.vx=vx;
        pa.vy=vy;
        pa.m=m;
        pa.y=y0-(1+E_rad)*2*((N-1)/E_p_length);
        pa.x=x0+(1+E_rad)*2*(N-1-((N-1)/E_p_length)*E_p_length);
        p[i]=pa;
    }
    double ro0=0;
    for (long i=0; i<tNum; i++)
    {
        ro0+=ro(p, i, h);
    }
    ro0=ro0/Num;
    for (long i=0; i<tNum; i++)
    {
        p[i].ro0=ro0;
    }
    for (long i=0; i<tNum; i++)
    {
        double cos, sin, rad, fluc;
        rad=randomize();
        cos=randomize();
        if (randomize(0, 1)==1)
            cos*=-1;
        sin=std::sqrt(1-cos*cos);
        if (randomize(0, 1)==1)
            sin*=-1;
        p[i].x+=cos*rad;
        p[i].y+=sin*rad;
        fluc=randomize();
        if (randomize(0, 1)==1)
            fluc*=-1;
        p[i].vx+=p[i].vx/10*fluc;
        fluc=randomize();
        if (randomize(0, 1)==1)
            fluc*=-1;
        p[i].vy+=p[i].vy/10*fluc;
    }
}
Particles::Particles (std::string c, double vx, double vy, double m, long int Num) //Asymptotics are analogic
{
    Particles(c, vx, vy, m, Num, this->h);
}
