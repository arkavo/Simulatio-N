#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define size 10000
#define timeStep 0.001
#define time 500
#define G 1
#define accuracy 0.01

//float field[size][size][size];

//TODO: Write code to automatically generate .m file for plotting the obtained data for n planets.
//DONE. But not working :P
//TODO: Add reading capabilities from  file.
//DONE. File must have data in the order: mass, position, velocity

FILE *proto;
FILE *table;
FILE *mfile;
FILE *data;

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

float root(float num){
	float guess = num/2;
	float prevGuess = 0;
	do{
		prevGuess = guess;
		guess = (guess + num/guess)/2;
	}
	while(prevGuess-guess > accuracy || guess - prevGuess > accuracy);
	return guess;
}

void initMFile(int n){
	fprintf(mfile, "data = importdata('Table.txt');\n");
	int i;
	for(i = 0; i < n; i++){
		fprintf(mfile, "plot(data(%d:2:end,1),data(%d:2:end,2))\n", i+1, i+1);
		fprintf(mfile, "hold on;\n");
	}
	fprintf(mfile, "saveas(gcf, 'plot.jpg')\n");
	return;
}


//Initializes a planet according to  input data
planet * initPlanet(){
	planet * p = (planet*)malloc(sizeof(planet));
	printf("NEW PLANET!\n");
	printf("Specify initial position:");
	scanf("%f%f%f", &p->pos.x,&p->pos.y,&p->pos.z);
	//printf("\n");
	printf("Specify initial velocity:");
	scanf("%f%f%f", &p->vel.x,&p->vel.y,&p->vel.z);
	//printf("\n");
	printf("Specify planet mass:");
	scanf("%f", &p->mass);
	printf("\n");
	return p;
}

planet * initPlanetFile(){
	planet * p = (planet*)malloc(sizeof(planet));
	fscanf(data,"%f", &p->mass);
	fscanf(data,"%f%f%f", &p->pos.x,&p->pos.y,&p->pos.z);
	fscanf(data,"%f%f%f", &p->vel.x,&p->vel.y,&p->vel.z);
	return p;
}

//Initializes a blank planet
planet * initPlanetArray(){
	planet * p = (planet*)malloc(sizeof(planet));
	return p;
}

//Following function prints current properties of a given planet to a file called lists.txt
void printPlanet(planet p){
	printf("Mass = %f\n", p.mass);
	printf("Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	printf("Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	fprintf(proto,"Mass = %f\n", p.mass);
	fprintf(proto,"Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	fprintf(proto,"Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	int i = 0;
	for(i = 0; i < 42; i++){
		printf("-");
	}
	printf("\n");
	return;
}

//Adds two vectors, returns the sum
vec addvec(vec v1, vec v2){
	vec nvec;
	nvec.x = v1.x + v2.x;
	nvec.y = v1.y + v2.y;
	nvec.z = v1.z + v2.z;
	return nvec;
}

//Subtracts vector 1 from vector 2, returns new vector
vec subvec(vec v1, vec v2){
	vec nvec;
	nvec.x = v1.x - v2.x;
	nvec.y = v1.y - v2.y;
	nvec.z = v1.z - v2.z;
	return nvec;
}

//Returns modulus of a vector
float mod(vec v){
	float m = v.x*v.x + v.y*v.y + v.z*v.z;
	return root(m);
}

//Multiplies vector by scalar, return the result
vec scalm(vec v, float scal){
	vec nvec;
	nvec.x = (v.x) * scal;
	nvec.y = (v.y) * scal;
	nvec.z = (v.z) * scal;
	return nvec;
}

void vecp(vec v){
	printf("%f %f %f\n", v.x, v.y, v.z);
	return;
}

//Takes the original planet array and calculates entries for new planet array
void iterate(planet ** orarray, planet ** newarray, int planetid, int tnum){
	int i = 0;
	vec acc;
	acc.x = 0; acc.y = 0; acc.z = 0; //Initialize the acceleration vector
	vec temp;
	temp.x = temp.y = temp.z = 0;
	float t, factor;
	if(tnum >= 1){
		for(i = 0; i < tnum; i++){
			if(i != planetid){
				temp = subvec((*(orarray[i])).pos,(*(orarray[planetid])).pos); //vector displacement
				t = mod(temp); //modulus of vector displacement
				factor = G * ((*(orarray[i])).mass)/(t*t*t);
				temp = scalm(temp, factor); //temp now contains the acceleration
				acc = addvec(acc, temp);
			}
		}
	}
	vec newpos = (*(orarray[planetid])).pos;
	vec mov = scalm((*(orarray[planetid])).vel,timeStep);//s = ut + 0.5at^2
	newpos = addvec(mov,newpos);
	t = 0.5*timeStep*timeStep;
	temp = scalm(acc,t);
	newpos = addvec(newpos, temp);
	(*(newarray[planetid])).pos = newpos;
	temp = scalm(acc, timeStep);
	(*(newarray[planetid])).vel = addvec((*(orarray[planetid])).vel,temp);
	(*(newarray[planetid])).mass = (*(orarray[planetid])).mass;
	return;
}

void tablePrint(planet p){
	fprintf(table, "%f %f %f\n", p.pos.x, p.pos.y, p.pos.z);
	return;
}	
	


int main(){
	int n;
	printf("Please enter number of required planets:");
	scanf("%d", &n);
	proto = fopen("List.txt","w+");
	table = fopen("Table.txt", "w+");
	mfile = fopen("Simul.m", "w+");
	data = fopen("Data.txt","r");
	initMFile(n);
	//fprintf(proto,"\n");
	//printf("\n");
	//fprintf(table,"Time\t");
	int i;
	planet** planetArray = (planet**)malloc(n*sizeof(planet *));
	planet** updateArray = (planet**)malloc(n*sizeof(planet *));
	for(i = 0; i < n; i++){
		//planetArray[i] = initPlanet();		//For manual input of planet data
		planetArray[i] = initPlanetFile();		//For file input of data
	}
	for(i = 0; i < n; i++){
		updateArray[i] = initPlanetArray();
	}
	int j;
	float t = 0;
	while(t < time){
		fprintf(proto,"Time: %f\n",t);
		//fprintf(table,"%f\n",t);
		printf("Time: %f\n", t);
		for(i = 0; i < n; i++){				//Prints out planet data before next iteration
			fprintf(proto,"Planet No: %d\n", i+1);
			tablePrint(*planetArray[i]);
			printf("Planet No: %d\n", i+1);
			printPlanet(*planetArray[i]);
		}
		for(j = 0; j < n; j++){
			iterate(planetArray, updateArray, j, n);
		}
		planet** temp = planetArray;
		planetArray = updateArray;	//Updated planet array becomes new planetArray for next iteration
		updateArray = temp;
		t = t + timeStep;
	}
	return 0;
}
