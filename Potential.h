#include <iostream>
#include "Vector.h"
#define min_pot -10000
int dirn[6] = {0};

vec move(int s,planet p,float Field[s][s][s])   //infinitesimal movement code.
{
    vec old_pos = p.pos;
    dirn[0] = Field[s][s][s+1];     //+z
    dirn[1] = Field[s][s][s-1];     //-z
    dirn[2] = Field[s][s+1][s];     //+y
    dirn[3] = Field[s][s-1][s];     //-y
    dirn[4] = Field[s+1][s][s];     //+x
    dirn[5] = Field[s-1][s][s];     //-x
    int i,j;
    float max = min_pot;
    for(i=0;i<6;i++)
    {
        if(max<dirn[i]) j=i;
    }
    switch(j)
        {
        case 0:
            p.pos.x1++;
            break;
        case 1:
            p.pos.x1--;
            break;
        case 0:
            p.pos.x2++;
            break;
        case 1:
            p.pos.x2--;
            break;
        case 0:
            p.pos.x3++;
            break;
        case 1:
            p.pos.x3--;
            break;
        }

}
