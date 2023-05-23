#pragma once
#include "Particles.hpp"
#include "ppair.hpp"
class Liquid
{
private:
    std::vector <particle> liq; //Vector of particles
    std::vector <std::vector<ppair>> DK; //Table of derivatives of the kernel function for each pair of particles in the distance range (0; h)
    double h;
    double alpha; //Pulse reduction coefficient after reflection from the walls and bottom
    double k; //Pressure coefficient
    double g; //Acceleration of free fall
    double dt; //Time change
public:
    Liquid (std::vector <Particles>& P, double alpha, double k, double g, double dt);
    double DerKer (particle p1, particle p2, double h); //Derivative of Kernel function
    void fillDK();
    void Solve(); //Computing of movement
    void Starting(); //Computing of some initial values
    void Visualize(); //Visualizer
    double derRo(unsigned int ind); //Density derivative
    double derE(unsigned int ind); //Derivative of specific kinetic energy
    double derVx(unsigned int ind); //Derivatives of velocity projections on the axises
    double derVy(unsigned int ind);
    double press(unsigned int ind); //Computing pressure
    void reflector(unsigned int ind); //Reflects particles from the walls and bottom
};
