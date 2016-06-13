#include <iostream>
#include "Potential.h"

#define size 100000;

float Field[size][size][size];

__global__ void main distribute(planet* gpu[])
{

}

int main()
{
  int n;
  cout<<"No of Planets";
  cin>>n;
  planet mem[n];
  planet* gpu[n];
  int i;
  for(i=0;i<n;i++)
  {
    mem[i] = init_planet();
    gpu[i] = cudaMalloc(planet**,sizeof(planet));
    cudaMemcpy(gpu[i],mem[i],sizeof(planet),cudaMemcpyHostToDevice);
  }
}
