#pragma once
#include "../../Classes&Structures/Liquid.hpp"
#include "../../Visualizer/Environment_Parameters.hpp"
void Liquid::reflector(unsigned int ind)
{
    double xmin=(E_WX-E_length)/2+E_rad;
    double xmax=(E_WX+E_length)/2-E_rad;
    double ymin=E_height+E_indent-E_rad;
    if (liq[ind].x<xmin)
    {
        liq[ind].x=xmin+alpha*(xmin-liq[ind].x);
        liq[ind].vx*=-alpha;
    }
    if (liq[ind].x>xmax)
    {
        liq[ind].x=xmax+alpha*(xmax-liq[ind].x);
        liq[ind].vx*=-alpha;
    }
    if (liq[ind].y<ymin)
    {
        liq[ind].y=ymin+alpha*(ymin-liq[ind].y);
        liq[ind].vy*=-alpha;
    }
}
