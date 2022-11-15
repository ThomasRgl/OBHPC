//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

//
#include "types.h"

//
#include "tools.h"

//
#include "kernels.h"

//
#include "rdtsc.h"

//
#define ALIGN64 64

//
#define MAX_SAMPLES 10

//
void run_benchmark(const ascii *title,
                   void ** (*kernel)(u64 iteration, void *restrict),
                   u64 n, u64 r);


//
int main(int argc, char **argv) {
    //
    srand(getpid());

    //
    if (argc < 2)
        return printf("usage: %s [r]\n", argv[0]), 1;

    // Number of kernel repetitions
    u64 r = atoll(argv[1]);

    // Print header
    printf("%10s; %15s; %15s; %15s; %10s; %10s; %15s; %15s; %15s; %26s; %10s; %10s\n",
           "titre", "KiB", "MiB", "GiB", "n", "r", "min", "max", "mean",
           "stddev (%)", "MiB/s", "titre");
    
    for (u64 i = 8; i < 24; i++ ){
        for(u64 j = 0; j < 20; j++){
            // run_benchmark("POINT", pointer_chasing, pow(2,i+j*0.1), r);
            run_benchmark("POINT", pointer_chasing, pow(2,i+j*0.05), r);
        
        }
         
    }

    //
    return 0;
}

//
void run_benchmark(const ascii *title,
                   void ** (*kernel)(u64 iteration, void *restrict),
                   u64 n, u64 r) {

    // Calculate the size of a single array
    u64 size = (sizeof(void *) * n );

    //
    f64 size_b = (float)size;
    f64 size_kib = size_b / (1024.0);
    f64 size_mib = size_b / (1024.0 * 1024.0);
    f64 size_gib = size_b / (1024.0 * 1024.0 * 1024.0);

    //
    f64 elapsed = 0.0;
    // struct timespec t1, t2;
    u64 t1, t2;

    f64 samples[MAX_SAMPLES];

    //
    void *restrict memblock = aligned_alloc(ALIGN64, size);
    u64 iteration = 10;

    //
    
    for (u64 i = 0; i < MAX_SAMPLES; i++) {
        //
        shuffle_pointer_adresses(memblock, n, 16 );
        
        //
        do {
            // clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            t1 = rdtsc();

            //for (u64 j = 0; j < r; j++)
                kernel(iteration, memblock);

            t2 = rdtsc();
            // clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

            elapsed = (f64)(t2 - t1) / (f64)(r * iteration * 16);
        } while (elapsed <= 0.0);

        samples[i] = elapsed;
    }
    
    //
    sort_f64(samples, MAX_SAMPLES);

    //
    f64 min = samples[0];
    f64 max = samples[MAX_SAMPLES - 1];
    f64 mean = mean_f64(samples, MAX_SAMPLES);
    f64 dev = stddev_f64(samples, MAX_SAMPLES);

    // Size in MiB / time in seconds
    // f64 mbps = size_mib / (mean / 1e9);
    f64 mbps = 0;

    //
    printf("%10s; %15.3lf; %15.3lf; %15.3lf; %10llu; %10llu; %15.3lf; %15.3lf; "
           "%15.3lf; %15.3lf (%6.3lf %%); %10.3lf; %10s\n",
           title,
           3 * size_kib, // 3 matices
           3 * size_mib, // 3 matrices
           3 * size_gib, // 3 matrices
           n, r, min, max, mean, dev, (dev * 100.0 / mean), mbps, title);

    //
    free(memblock);
}
