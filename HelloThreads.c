/*
Extend the program below to make it parallel where every 
thread prints out it's id and total number of threads.
*/

#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel 
	{
	printf("hello from thread: %i out of %i \n", omp_get_thread_num(), omp_get_num_threads()); 
	}

return 0; 
}