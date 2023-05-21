#pragma once
#include <stdlib.h>
#include <time.h>

int randomize(int max, int min) //Returns value [min; max]^Z
{
    srand(time(NULL));
    return min+rand()%(max-min+1);
}

double randomize() //Returns value [0; 1]
{
    double d=0;
    for (int i=0; i<7; i++)
    {
        d*=10;
        d+=randomize(9, 0);
    }
    if (d==9999999)
        return 1;
    else
    {
        for (int i=0; i<7; i++)
        {
            d=d/10;
        }
        return d;
    }
}
