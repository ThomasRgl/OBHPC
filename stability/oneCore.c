#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//
#include "types.h"

//
#define ALIGN64 64


//
void run_benchmark(const ascii *title, u64 n, u64 r, u64 sample);

//
int main(int argc, char **argv) {
    //
    srand(getpid());

    //
    if (argc < 4)
        return printf("usage: %s [n] [r] [sample] \n", argv[0]), 1;

    // Number of array elements
    u64 n = atoll(argv[1]);

    // Number of kernel repetitions
    u64 r = atoll(argv[2]);
    
    u64 sample = atoll(argv[3]);

    // Print header
    printf("%10s; %10s; %10s; %20s; %20s; \n",
           "core Id", "N", "r", "time ns", "GHz" );

    run_benchmark("",  n, r, sample);

    //
    return 0;
}

//
void run_benchmark(const ascii *title, u64 N, u64 r, u64 sample) {


    //
    f64 elapsed = 0.0;
    struct timespec t1, t2;


    //
    for (u64 i = 0; i < sample; i++) {
        do {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

            for (u64 j = 0; j < r; j++){
                // printf("hello there\n");
                __asm__ volatile (
                    "loop1:;\n"
                    "dec %[_N];\n"
                    "jnz loop1;\n"
                    :
                    : [_N] "r" (N)
                    : "cc", "memory" );
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

            elapsed = (f64)(t2.tv_nsec - t1.tv_nsec) / (f64)r;
        } while (elapsed <= 0.0);

        // samples[i] = elapsed;
        f64 measure_freq = N / elapsed ;

        printf("%10llu; %10llu; %10llu; %20.5lf; %20.5lf; \n", 
           i, N, r, elapsed, measure_freq  );


    }
    

    //
    }
