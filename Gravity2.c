#include<stdio.h>
#include<stdlib.h>

#define size 10000
#define timeInc 0.01

float field[size][size][size];

typedef struct vector{
	float x;
	float y;
	float z;
} v;

typedef struct planet{
	float mass;
	v pos;
	v vel;
	//v acc;	
} p;

v input(p planet){
	printf("m,x,y,z,vx,vy,vz in order:");
	scanf("%f,%f,%f,%f,%f,%f,%f",&p.mass,&p.pos.x,


p init_planet(float mass, v position, v velocity){
	//malloc 
	p.vel = velocity;
	p.pos = position;
	return p;
}

int main(){
	p p1 = init_planet();
	p p2 = init_planet();
	
	
	return 0;
}
