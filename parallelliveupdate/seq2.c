#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

#define timeStep 0.01
#define G 1
#define accuracy 0.01
#define n 3

FILE *data1;
FILE *data2;
FILE *table;
FILE *plot;

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

#pragma acc routine
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

planet * initPlanetFile(){
	planet * p = (planet*)malloc(sizeof(planet));
	fscanf(data2,"%f", &p->mass);
	fscanf(data2,"%f%f%f", &p->pos.x,&p->pos.y,&p->pos.z);
	fscanf(data2,"%f%f%f", &p->vel.x,&p->vel.y,&p->vel.z);
	return p;
}

//Initializes a blank planet
planet * initPlanetArray(){
	planet * p = (planet*)malloc(sizeof(planet));
	return p;
}

//Following function prints current properties of a given planet to a file called lists.txt
void printPlanet(planet p){
	fprintf(plot,"%f\t%f\t%f\n", p.pos.x, p.pos.y, p.pos.z);
	//fprintf(table,"\n%f\t%f\t%f\n", p.pos.x, p.pos.y, p.pos.z);
	return;
}

//Takes the original planet array and calculates entries for new planet array
#pragma acc routine
void iterate(planet ** orarray, planet ** newarray, int planetid, int tnum){
	int i = 0;
	vec a, b;
	float accx = 0;
	float accy = 0;
	float accz = 0;
	float t, factor, delx, dely, delz, m;
	if(tnum >= 1){
		for(i = 0; i < tnum; i++){
			if(i != planetid){
				a = (*(orarray[i])).pos;
				b = (*(orarray[planetid])).pos;
				delx = a.x - b.x;
				dely = a.y - b.y;
				delz = a.z - b.z;
				m = (*(orarray[i])).mass;	
				t = delx*delx + dely*dely + delz*delz;
			        t = root(t);	
				factor = (G * m)/(t*t*t);
						accx += factor*delx;
				accy += factor*dely;
				accz += factor*delz;
			}
		}
	}
	float posx = (*(orarray[planetid])).pos.x;
	float posy = (*(orarray[planetid])).pos.y;
	float posz = (*(orarray[planetid])).pos.z;
	posx += (*(orarray[planetid])).vel.x*timeStep;//s = ut + 0.5at^2
	posy += (*(orarray[planetid])).vel.y*timeStep;
	posz += (*(orarray[planetid])).vel.z*timeStep;
	float delvecx = accx*timeStep;
	float delvecy = accy*timeStep;
	float delvecz = accz*timeStep;
	t = 0.5*timeStep*timeStep;
	accx *= t;
	accy *= t;
	accz *= t;
	posx += accx;
	posy += accy;
	posz += accz;
	(*(newarray[planetid])).pos.x = posx;
	(*(newarray[planetid])).pos.y = posy;
	(*(newarray[planetid])).pos.z = posz;
	(*(newarray[planetid])).vel.x = (*(orarray[planetid])).vel.x + delvecx;
	(*(newarray[planetid])).vel.y = (*(orarray[planetid])).vel.y + delvecy;
	(*(newarray[planetid])).vel.z = (*(orarray[planetid])).vel.z + delvecz;;
	(*(newarray[planetid])).mass = (*(orarray[planetid])).mass;
	return;
}

void newData(planet p){
	fprintf(data1, "%f\t", p.mass);
	fprintf(data1, "%f\t%f\t%f\t", p.pos.x, p.pos.y, p.pos.z);
	fprintf(data1, "%f\t%f\t%f\n", p.vel.x, p.vel.y, p.vel.z);
	return;
}	
	


int main(){
	//int n;
	//printf("Please enter number of planets:\n");
	//scanf("%d", &n);
	plot = fopen("List.txt","w");
	table = fopen("Table.txt", "a");
	data1 = fopen("Data1.txt","w+");
	data2 = fopen("Data2.txt", "r");
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
#pragma acc kernels
	for(j = 0; j < n; j++){
		iterate(planetArray, updateArray, j, n);
	}
	for(i = 0; i < n; i++){
		newData(*updateArray[i]);
		printPlanet(*updateArray[i]);
	}
	return 0;
}
	