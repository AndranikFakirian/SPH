#pragma once
#include "../Classes&Structures/Liquid.hpp"

void Liquid::Solve() //Speed - O(N)
{
    fillDK();
    for (unsigned i=0; i<liq.size(); i++)
    {
        liq[i].dro=derRo(i)*dt;
        liq[i].dvx=derVx(i)*dt;
        liq[i].dvy=(derVy(i)+g)*dt;
    }
    for (unsigned i=0; i<liq.size(); i++)
    {
        liq[i].ro+=liq[i].dro;
        liq[i].vx+=liq[i].dvx;
        liq[i].vy+=liq[i].dvy;
        liq[i].p=press(i);
        liq[i].x+=liq[i].vx*dt;
        liq[i].y+=liq[i].vy*dt;
    }
}
