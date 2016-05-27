#include <vector>
#include <iostream>
using namespace std;

class Body

{
    int mass;
    int radius;
    vector<float> pos (3,0);
    vector<float> vel (3,0);
    //std::vector<float> acc (3,0);     unneeded for now
};

void input(Body planet)
{
    cout<<"Input mass,radius,position(x,y,z),velocity(x,y,z)";
    cin>>planet.mass,planet.radius,planet.pos.x,planet.pos.y,planet.pos.z,planet.vel.x,planet.vel.y,planet.vel.z;
}

int main()
{
    //input function.
}
