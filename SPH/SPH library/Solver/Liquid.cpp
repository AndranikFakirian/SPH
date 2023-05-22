#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include "kerfunc.cpp"

void Liquid::fillDK() //Speed - O(n^2), memory - O(n)
{
    long i=0;
    DK.resize(liq.size());
    for (const auto &it : liq)
    {
        DK[i].resize(liq.size());
        long j=0;
        for (const auto &it1 : liq))
        {
            double dk=DerKer(it, it1, h);
            if (dk!=0)
            {
                ppair p;
                p.pparticle=it1;
                p.dk=dk;
                DK[i][j]=p;
                j++;
            }
        }
        DK[i].resize(j);
        i++;
    }
}
