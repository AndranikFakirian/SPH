#pragma once
#include "../Classes&Structures/Liquid.hpp"
#include "SPHfunc.cpp"

void Liquid::Starting() //Speed - O(N)
{
    for (long i=0; i<liq.size(); i++)
    {
        liq[i].ro=ro(liq, i, h);
        liq[i].p=press(i);
    }
}
