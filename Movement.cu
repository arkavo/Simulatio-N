#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "Sequence.h"

#define size 100000;                                    //space size
#define t 0.0001;                                       //timeStep

using namespace std;

float Field[size][size][size]={0};


__global__ void Movement(planet* pl,vec force)
{
  pl->pos.x1 += (*pl).vel.x1 * t;
  pl->pos.x2 += (*pl).vel.x2 * t;
  pl->pos.x3 += (*pl).vel.x3 * t;

  pl->vel.x1 += ((force.x1)/((*pl).mass)) * t;
  pl->vel.x2 += ((force.x2)/((*pl).mass)) * t;
  pl->vel.x3 += ((force.x3)/((*pl).mass)) * t;
}


int main(void)
{
  int n;                                               //planet counter
  int i=0;                                             //counter variable
  int j;
  int* t_mass;
  vec* t_pos;


  cout<<"Input number of bodies:\n";
  cin>>n;
  Body* List[n];
  for(i=0;i<n;i++)
  {
      List[i]=cudaMalloc((void**)&Body,sizeof(Body));
      List[i]->vel = {0};
      cout<<"mass and postion of"<<i+1<<"th Body?\n";
      cin>>List[i]->mass>>List[i]->x>>List[i]->y>>List[i]->z;
      cudaMemcpy(t_mass,List[i].mass,sizeof(float),cudaMemcpyHostToDevice);
      for(j=0;j<3;j++)
        cudaMemcpy(t_pos[j],List[i].pos[j],sizeof(float),cudaMemcpyHostToDevice);
  }
}
