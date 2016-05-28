#include <iostream>
#include <cstdlib>
#include <vector>

#define size 100000;                                    //space size
#define t 0.0001;

using namespace std;

float Field[size][size][size]={0};

class Body                                              //basic planet properties
{
  public:
    float mass;
    vector<float> pos (3,0);
    vector<float> vel (3,0);
};

__global__ void Movement(Body* planet,vector<float> force)
{
  
}


int main(void)
{
  int n;                                               //planet counter
  int i=0;                                             //counter variable
  int j;
  int* t_mass;
  vector<float>* t_pos (3,0);


  cout<<"Input number of bodies:\n";
  cin>>n;
  Body* List[n];
  for(i=0;i<n;i++)
  {
      List[i]=cudaMalloc((void**)&Body,sizeof(Body));
      List[i]->vel = (0,0,0);
      cout<<"mass and postion of"<<i+1<<"th Body?\n";
      cin>>List[i]->mass>>List[i]->x>>List[i]->y>>List[i]->z;
      cudaMemcpy(t_mass,List[i].mass,sizeof(float),cudaMemcpyHostToDevice);
      for(j=0;j<3;j++)
        cudaMemcpy(t_pos[j],List[i].pos[j],sizeof(float),cudaMemcpyHostToDevice);
  }
}
