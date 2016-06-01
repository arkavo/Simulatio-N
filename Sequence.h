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

void initMFile(int n)
{
	fprintf(mfile, "data = importdata('Table.txt');\n");
	int i;
	for(i = 0; i < n; i++){
		fprintf(mfile, "plot(data(%d:2:end,1),data(%d:2:end,2))\n", i+1, i+1);
		fprintf(mfile, "hold on;\n");
	}
	fprintf(mfile, "saveas(gcf, 'plot.jpg')\n");
	//return; //The hell you return from void?
}

planet *initPlanet()
{
	planet * p = (planet*)malloc(sizeof(planet));
	cout<<"New Planet!\n";
	cout<<"Specify initial position:";
	cin>>&p->pos[0],&p->pos[1],&p->pos[2];
	//printf("\n");
	cout<<"Specify initial velocity:";
	cin>>&p->vel[0],&p->vel[1],&p->vel[2];
	//printf("\n");
	cout<<"Specify planet mass:";
	cin>>&p->mass;
	cout<<"\n";
	return p;
}

planet *initPlanetFile(string name[])
{
	planet * p = (planet*)malloc(sizeof(planet));
	fscanf(name, &p->mass);
	fscanf(name, &p->pos[0],&p->pos[1],&p->pos[2]);
	fscanf(name, &p->vel[0],&p->vel[1],&p->vel[2]);
	return p;
}

void printPlanet(planet p)
{
	cout<<"Mass = %f\n">>p.mass;
	cout<<"Position = (%f, %f, %f)\n">>p.pos.x, p.pos.y, p.pos.z;
	cout<<"Velocity = (%f, %f, %f)\n">>p.vel.x, p.vel.y, p.vel.z;
	fprintf(proto,"Mass = %f\n", p.mass);
	fprintf(proto,"Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	fprintf(proto,"Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	int i = 0;
	for(i = 0; i < 42; i++){
		printf("-");
	}
	cout<<"\n";
	return;
}

void iterate(planet** orarray, planet** newarray, int planetid, int tnum)
{
	int i = 0;
	vec acc (3,0);
	//acc.x = 0; acc.y = 0; acc.z = 0; //Initialize the acceleration vector
	vec temp (3,0);
	//temp.x = temp.y = temp.z = 0;
	float t, factor;
	if(tnum >= 1)
    {
		for(i = 0; i < tnum; i++)
        {
			if(i != planetid)
            {
				temp = subvec((*(orarray[i])).pos,(*(orarray[planetid])).pos); //vector displacement
				t = mod(temp); //modulus of vector displacement
				factor = G * ((*(orarray[i])).mass)/(t*t*t);
				temp = temp*factor; //temp now contains the acceleration
				acc = acc+temp);
			}
		}
	}
	vec newpos = (*(orarray[planetid])).pos;
	vec mov = (*(orarray[planetid])).vel*timeStep;//s = ut + 0.5at^2
	newpos = mov+newpos;
	t = 0.5*timeStep*timeStep;
	temp = acc*t;
	newpos = addvec(newpos, temp);
	(*(newarray[planetid])).pos = newpos;
	temp = acc*timeStep;
	(*(newarray[planetid])).vel = (*(orarray[planetid])).vel+temp;
	(*(newarray[planetid])).mass = (*(orarray[planetid])).mass;
	//return; void no return
}

void tablePrint(planet p)
{
	fprintf(table, "%f %f %f\n", p.pos[0], p.pos[1], p.pos[2]);
	//return;
}





#endif
