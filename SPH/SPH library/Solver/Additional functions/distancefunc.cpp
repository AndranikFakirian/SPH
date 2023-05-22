#pragma once
#include "../../Classes&Structures/particle.cpp"
double dist(particle p1, particle p2)
{
    double dr=pow(p1.x-p2.x, 2)+pow(p1.y-p2.y, 2);
    return pow(dr,0.5);
}
