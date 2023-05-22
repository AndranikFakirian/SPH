#pragma once
#include "particle.cpp"
#include <vector>
class Particles
{
private:
    std::vector <particle> p; //Vector of particles
public:
    static long int N; //Number of particles
    static double h; //Kernel radius
    Particles (std::string c, double vx, double vy, double m, long int Num, double h); //Constructs vector with Num particles (if Num+N>maxNumOfParticles => with maxNumOfParticles-N) coordinates and velocities of which is artificially fluctuated
    Particles (std::string c, double vx, double vy, double m, long int Num); //Constructor if h is already known
    std::vector <particle> getParticles();
};
long int Particles::N=0;
double Particles::h=0;
