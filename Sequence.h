#ifndef "Sequence.h"
#define "Sequence.h"

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>

using namespace std;

#define size 10000
#define timeStep 0.0001
#define time 2
#define G 1
#define accuracy 0.01

#typedef vector<float> vec;
// class vector
// {
//     float x;
//     float y;
//     float z;
// };

class planet
{
    float mass;
    vec pos = {0,0,0};
    vec vel = {0,0,0};
};

float root(float num)
{
	float guess = num/2;
	float prevGuess = 0;
	do
    {
		prevGuess = guess;
		guess = (guess + num/guess)/2;
	}
	while(prevGuess-guess >= accuracy || guess - prevGuess > accuracy);
	return guess;
}
// I cant initplane here leve it to the CUDA part

float vecmod(vec a)                         //vector magnitude
{
    return pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),(1/2));
}


#endif
