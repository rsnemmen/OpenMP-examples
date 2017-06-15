#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel 
	{
		printf("Hi fucking world\n");
	}

	return 0; 
}