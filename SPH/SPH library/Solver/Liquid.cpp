#pragma once
#include "../Classes&Structures/Liquid.hpp"

void Liquid::fillDK() //Speed - O(n^2), memory - O(n)
{
    long i=0;
    DK.resize(liq.size());
    for (vector <particle>::iterator it=liq.begin(); it!=liq.end(); ++it)
    {
        DK[i].resize(liq.size());
        long j=0;
        for (vector <particle>::iterator it1=liq.begin(); it1!=liq.end(); ++it1)
        {
            double dk=DerKer((*it), (*it1), h);
            if (dk!=0)
            {
                ppair p;
                p.pparticle=(*it1);
                p.dk=dk;
                DK[i][j]=p;
                j++;
            }
            DK[i].resize(j);
        }
        i++;
    }
}
