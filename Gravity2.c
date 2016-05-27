#include<stdio.h>
#include<stdlib.h>

#define size 10000
#define timeInc 0.01

//float field[size][size][size];

typedef struct vector{
	float x;
	float y;
	float z;
} vec;

typedef struct planets{
	float mass;
	vec pos;
	vec vel;	
} planet;

//typedef struct planets planet;

planet * initPlanet(){
	planet * p = (planet*)malloc(sizeof(planet));
	printf("NEW PLANET!\n");
	printf("Specify initial position:");
	scanf("%f%f%f", &p->pos.x,&p->pos.y,&p->pos.z);
	printf("\n");
	printf("Specify initial velocity:");
	scanf("%f%f%f", &p->vel.x,&p->vel.y,&p->vel.z);
	printf("\n");
	printf("Specify planet mass:");
	scanf("%f", &p->mass);
	printf("\n");
	return p;
}

void printPlanet(planet p){
	printf("Mass = %f\n", p.mass);
	printf("Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	printf("Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	int i = 0;
	for(i = 0; i < 42; i++){
		printf("-");
	}
	printf("\n");
	return;
}


int main(){
	int n;
	printf("Please enter number of required planets:");
	scanf("%d", &n);
	printf("\n");
	planet** planetArray = (planet**)malloc(n*sizeof(planet *));
	int i;
	for(i = 0; i < n; i++){
		planetArray[i] = initPlanet();
	}
	for(i = 0; i < n; i++){
		printf("Planet No: %d\n", i+1);
		printPlanet(*planetArray[i]);
	}	
	return 0;
}
