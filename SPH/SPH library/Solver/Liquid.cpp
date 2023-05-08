#pragma once
#include "../Classes&Structures/Liquid.hpp"

void Liquid::fillDK()
{
    vector<particle>::iterator it;
    int i=0;
    for (it=liq.begin(); it!=liq.end(); ++it)
    {
        vector<particle>::iterator it1;
        for (it1=liq.begin(); it1!=liq.end(); ++it1)
        {
            DK[i].pushback(DerKer(it, it1, h))
        }
        i++;
    }
}
