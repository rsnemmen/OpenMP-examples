/*
Create a program that computes a simple matrix vector multiplication 
b=Ax, either in fortran or C/C++. Use OpenMP directives to make 
it run in parallel.

This is the parallel version.
*/

#include <stdio.h>
#include <omp.h>

int main() {
	float A[2][2] = {{1,2},{3,4}};
	float b[] = {8,10};
	float c[2];
	int i,j;

	// computes A*b
	#pragma omp parallel for
	for (i=0; i<2; i++) {
		c[i]=0;
		for (j=0;j<2;j++) {
			c[i]=c[i]+A[i][j]*b[j];
		}
	}

	// prints result
	for (i=0; i<2; i++) {
		printf("c[%i]=%f \n",i,c[i]);
	}

return 0; 
}