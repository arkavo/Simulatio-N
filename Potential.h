#include <Vector.h>

typedef struct planet
{
    float mass;
    vector pos;
    vector vel;
}planet;

planet init_planet()
{
    planet Pt;
    cout<<"Mass";
    cin>>Pt.mass;
    cout<<"Position";
    cin>>Pt.pos.x1>>Pt.pos.x2>>Pt.pos.x3;
    cout<<"Velocity";
    cin>>Pt.vel.x1>>Pt.vel.x2>>Pt.vel.x3;
    return Pt;
}
