#pragma once
#include "Particles.hpp"
class Liquid
{
private:
    vector <particle> liq;
    vector <vector <double>> DK;
public:
    Liquid (vector <Particles> P);
    double Ker (particle p1, particle p2, double h); //Kernel function
    double DerKer (particle p1, particle p2, double h); //Derivative of Kernel function
};