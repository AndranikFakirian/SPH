#pragma once
#include "particle.cpp"
#include <vector>
class Particles
{
private:
    vector <particle> p; //Vector of particles
public:
    static long int N; //Number of particles
    static double h; //Kernel radius
    double Ker(particle p1, particle p2, double h); //Kernel function
    double ro(vector <particle> liq, unsigned int ind, double h); //Computing densities of particles
    Particles (string c, double vx, double vy, double m, long int Num, double h); //Constructs vector with Num particles (if Num+N>maxNumOfParticles => with maxNumOfParticles-N) coordinates and velocities of which is artificially fluctuated
    Particles (string c, double vx, double vy, double m, long int Num); //Constructor if h is already known
    vector <particle> getParticles();
};
long int Particles::N=0;
double Particles::h=0;
