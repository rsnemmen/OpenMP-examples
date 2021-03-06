/******************************************************************************

we generate "iter" random numbers, each of which will be the upper limit of
the integration of a function (see below)

    f(x) = x^2*cos(x)*exp(x)
    f(x) = sin(x)*exp(x)/(x + 1.)

list of program functions:

    func   is the function to be integrated
    integ  is the integration routine (Simpson 3/8 rule)

Using iter=1000000000, this takes about 10 seconds on a single core.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double func(double x){
//    return x*x*cos(x)*exp(x);
    return sin(x)*exp(x)/(x + 1.);
}

void integ(double upper){
    int i, n;
    double lower, step, sum, result;

    n = 10000; // may change this
    lower = 0.;
    step  = (upper - lower)/n;

    sum = func(lower) + func(upper);
    for (i = 1; i < n; i++){
        if (i % 3 == 0){
            sum = sum + 2.*func(lower + i*step);
        }
        else {
            sum = sum + 3.*func(lower + i*step);
        }
    }
    result = (3.*step/8.)*sum;
}

int main(int argc, char *argv[]){

    clock_t tic, toc;
    int i, iter;
    double limit;

    tic = clock();

    // read command-line argument
    if ( argc != 2 ) {
        printf( "Usage: %s n \n", argv[0] );
        exit(0);
    }     
    sscanf(argv[1], "%d", &iter);

    srand(time(NULL));

    for (i = 0; i < iter; i++){
        limit = rand() % 200;
        integ(limit);
    }

    toc = clock();
    printf("Elapsed time: %f seconds\n", (double)(toc - tic)/CLOCKS_PER_SEC);

    return(0);
}
