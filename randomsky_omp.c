/* 
Write code that generates random points in the sky. This will be 
based off randomsky.f90. Write the events
in a text or binary file.

Usage: randomsky n

:param n: = number of desired points

This will be a good exercise in doing Monte Carlo simulations
in C.

TODO:

- [x] input parameters from the command-line
- [x] dynamically allocate arrays
- [x] Monte Carlo
- [ ] write binary file?

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	int ntarget, i;
	float *xa, *ya; 
	float x, y, sampling, exposure;

	// read command-line argument
	if ( argc != 2 ) {
        printf( "Usage: %s ncosmic_rays \n", argv[0] );
        exit(0);
    } 
    sscanf(argv[1], "%i", &ntarget); 

    // dynamically allocate arrays
	xa = (float *)malloc(sizeof(float)*ntarget); 
	ya = (float *)malloc(sizeof(float)*ntarget); 

	// Equatorial coordinates of accepted events
	memset(xa, 0, sizeof(int)*ntarget); // initializes array to zeroes
	memset(ya, 0, sizeof(int)*ntarget);

	/* Performs the Monte Carlo simulation
	Be careful here. Distributing points uniformly in the (alpha,delta)
	plane does not correspond to a uniform random sky (spherical surface).
	Instead it will concentrate points towards the poles of the sphere.
	*/

	// initialize pseudo-random number generator
    srand(time(NULL)); 

	/* 
	Loop that produces individual CRs
	==================================
	Several things can be learned by optimizing the loop below. First
	of all, if you do not specify which variables are private to each
	thread, they may think they are shared and will try to write at the
	same time, causing a running condition where the code waits for 
	sequential writing. This slows down things.

	*/

	#pragma omp parallel for private(x,y,i) 
	for (i=0; i<ntarget; i++) {
		// random number between 0 and 360 
		x=((float)rand()/(float)(RAND_MAX)) * 360.;
		// random number between 0 and 1
		y=((float)rand()/(float)(RAND_MAX));

		// To avoid concentrations towards the poles, generates sin(delta)
		// between -1 and +1, then converts to delta
		y = asin(2.*y-1.)*180./M_PI;	// dec

		/* this is a bottleneck for parallelization: if you 
		comment out these lines, we will achieve almost
		perfect optimization!

		it is not trivial to gain speed here
		*/
		xa[i]=x; 
		ya[i]=y;
	}

	/*
	for (i=0; i<ntarget; i++) {
		printf("%f %f -- ", xa[i],ya[i]);
	}
	*/



	return(0);	
}