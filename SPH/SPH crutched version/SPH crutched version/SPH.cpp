#include "SPH crutched library/The Great Crutch.hpp"

int main()
{
    Particles p1("blue", 1, 1, 1, 3150, 10);
    Particles p2("red", 1, 1, 1, 3150);
    std::vector <Particles> P={p1, p2};
    Liquid L(P, 1, 1, 1, 0.00001);
    L.Visualize();

    return 0;
}
