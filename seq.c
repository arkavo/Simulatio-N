#pragma warning(disable:4996)//to disable the warning for scanf and all such functions realted to their safety
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define size 10000
#define timeStep 0.001
#define time 2
#define G 1
#define accuracy 0.01


//float field[size][size][size];

FILE *proto;
FILE *proto2;

typedef struct vector {
	float x;
	float y;
	float z;
} vec;

typedef struct planets {
	float mass;
	vec pos;
	vec vel;
	int fixed;
} planet;

float root(float num) {
	float guess = num / 2;
	float prevGuess = 0;
	do {
		prevGuess = guess;
		guess = (guess + num / guess) / 2;
	} while (prevGuess - guess > accuracy || guess - prevGuess > accuracy);
	return guess;
}
//Initializes a planet according to  input data
planet * initPlanet() {
	planet * p = (planet*)malloc(sizeof(planet));
	printf("NEW PLANET!\n");
	printf("Specify initial position:");
	scanf("%f%f%f", &p->pos.x, &p->pos.y, &p->pos.z);
	printf("\n");
	printf("Do you want the planet to be fixed? Y or N?\n (Just in case you want to simulate a situation similar to rotation of planets around Sun, keeping the Sun fixed.)");
	scanf("%d", &p->fixed);
	printf("\n");
	if (p->fixed == 1) {
		p->vel.x = 0;
		p->vel.y = 0;
		p->vel.z = 0;
	}
	else {
		printf("Specify initial velocity:");
		scanf("%f%f%f", &p->vel.x, &p->vel.y, &p->vel.z);
		printf("\n");
	}
	printf("Specify planet mass:");
	scanf("%f", &p->mass);
	printf("\n");
	return p;
}
//Initializes a blank planet
planet * initPlanetArray() {
	planet * p = (planet*)malloc(sizeof(planet));
	return p;
}
//Following function prints current properties of a given planet to a file called lists.txt
void printPlanet(planet p) {
	printf("Mass = %f\n", p.mass);
	printf("Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	printf("Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	fprintf(proto, "Mass = %f\n", p.mass);
	fprintf(proto, "Position = (%f, %f, %f)\n", p.pos.x, p.pos.y, p.pos.z);
	fprintf(proto, "Velocity = (%f, %f, %f)\n", p.vel.x, p.vel.y, p.vel.z);
	int i = 0;
	for (i = 0; i < 42; i++) {
		printf("-");
	}
	printf("\n");
	return;
}
void printPlanetGraph(planet p) {
	fprintf(proto2, "%f,%f,%f", p.pos.x, p.pos.y, p.pos.z);
	return;
}
//Adds two vectors, returns the sum
vec addvec(vec v1, vec v2) {
	vec nvec;
	nvec.x = v1.x + v2.x;
	nvec.y = v1.y + v2.y;
	nvec.z = v1.z + v2.z;
	return nvec;
}
//Subtracts vector 1 from vector 2, returns new vector
vec subvec(vec v1, vec v2) {
	vec nvec;
	nvec.x = v1.x - v2.x;
	nvec.y = v1.y - v2.y;
	nvec.z = v1.z - v2.z;
	return nvec;
}

//Returns modulus of a vector
float mod(vec v) {
	float m = v.x*v.x + v.y*v.y + v.z*v.z;
	return root(m);
}

//Multiplies vector by scalar, return the result
vec scalm(vec v, float scal) {
	vec nvec;
	nvec.x = (v.x) * scal;
	nvec.y = (v.y) * scal;
	nvec.z = (v.z) * scal;
	return nvec;
}

//TODO: Write a code to print the whole planet array to a file
//DONE ignore previous line

void vecp(vec v) {
	printf("%f %f %f\n", v.x, v.y, v.z);
	return;
}

//Takes the original planet array and calculates entries for new planet array
void iterate(planet ** orarray, planet ** newarray, int planetid, int tnum) {
	int i = 0;
	vec acc;
	acc.x = 0; acc.y = 0; acc.z = 0; //Initialize the acceleration vector
	vec temp;
	temp.x = temp.y = temp.z = 0;
	float t, factor;
	if (tnum >= 1) {

		for (i = 0; i < tnum; i++) {
			if (i != planetid) {
				temp = subvec((*(orarray[i])).pos, (*(orarray[planetid])).pos); //vector displacement
																				//vecp(temp);
				t = mod(temp); //modulus of vector displacement
							   //printf("%f\n", t);
				factor = G * ((*(orarray[i])).mass) / (t*t*t);
				temp = scalm(temp, factor); //temp now contains the acceleration
				acc = addvec(acc, temp);
			}
		}
	}
	//vecp(acc);
	vec newpos = (*(orarray[planetid])).pos;
	//vecp(newpos);
	vec mov = scalm((*(orarray[planetid])).vel, timeStep);//s = ut + 0.5at^2
														  //vecp(mov);
	newpos = addvec(mov, newpos);
	t = 0.5*timeStep*timeStep;
	temp = scalm(acc, t);
	//vecp(temp);
	newpos = addvec(newpos, temp);
	//vecp(newpos);
	(*(newarray[planetid])).pos = newpos;
	temp = scalm(acc, timeStep);
	(*(newarray[planetid])).vel = addvec((*(orarray[planetid])).vel, temp);
	(*(newarray[planetid])).mass = (*(orarray[planetid])).mass;
	return;
}

int main() {
	int nthreads2, tid2, procs, maxt, inpar, dynamic, nested;
#pragma omp parallel private(nthreads2, tid2)
	{

		/* Obtain thread number */
		tid2 = omp_get_thread_num();

		/* Only master thread does this */
		if (tid2 == 0)
		{
			printf("Thread %d getting environment info...\n", tid2);

			/* Get environment information */
			procs = omp_get_num_procs();
			nthreads2 = omp_get_num_threads();
			maxt = omp_get_max_threads();
			inpar = omp_in_parallel();
			dynamic = omp_get_dynamic();
			nested = omp_get_nested();

			/* Print environment information */
			printf("Number of processors = %d\n", procs);
			printf("Number of threads = %d\n", nthreads2);
			printf("Max threads = %d\n", maxt);
			printf("In parallel? = %d\n", inpar);
			printf("Dynamic threads enabled? = %d\n", dynamic);
			printf("Nested parallelism enabled? = %d\n", nested);

		}

	}

	/* Start parallel region */
	/* Done */
	clock_t start, end;//to measure the running time of the process.
	start = clock();
	int n;
	printf("Please enter number of required planets:");
	scanf("%d", &n);
	proto = fopen("List.csv", "w+");
	proto2 = fopen("Graph.csv", "w+");
	fprintf(proto, "n");
	printf("\n");
	planet** planetArray = (planet**)malloc(n * sizeof(planet *));
	planet** updateArray = (planet**)malloc(n * sizeof(planet *));
	int i;
	for (i = 0; i < n; i++) {
		planetArray[i] = initPlanet();
	}
	for (i = 0; i < n; i++) {
		updateArray[i] = initPlanetArray();
	}
	int j;
	float t = 0;
	int p = 0;
	int nthreads, tid;
	while (t < time) {
		fprintf(proto, "Time: %f\n", t);
		printf("Time: %f\n", t);
		for (i = 0; i < n; i++) {				//Prints out planet data before next iteration
			fprintf(proto2, "Planet No: %d\n", i + 1);
			printf("Planet No: %d\n", i + 1);
			printPlanet(*planetArray[i]);
			printPlanetGraph(*planetArray[0]);
			printPlanetGraph(*planetArray[1]);
			fprintf(proto2, "\n");
		}

#pragma omp parallel num_threads(64)
		{

#pragma omp for
			for (j = 0; j < n; j++) {
				iterate(planetArray, updateArray, j, n);
			}
			tid = omp_get_thread_num();
			nthreads = omp_get_num_threads();
			if (tid == 0) {
				printf("numer of threads=%d\n", nthreads);
			}
			planet** temp = planetArray;
			planetArray = updateArray;	//Updated planet array becomes new planetArray for next iteration
			updateArray = temp;
			t = t + timeStep;
		}
	}
	/*for(i = 0; i < n; i++){
	printf("Planet No: %d\n", i+1);
	printPlanet(*planetArray[i]);
	}*/
	/*vec v1; v1.x = 1; v1.y = 0; v1.z = 0;
	printf("%f", mod(v1));*/
	//there is really no dende in doing this coz this takes much more longer
	end = clock();
	double clock_time = end - start;
	double time_taken = clock_time / CLOCKS_PER_SEC;//in seconds
													//printf("Time taken by processor to execute the function: %lf seconds\n",time_taken);
	//system("chmod +x go.sh");
	//system("./go.sh");
	getchar();
	return 0;
}
