#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>


//
#include "types.h"

typedef struct thread_args
{
    u64 n;
    u64 r;
    u64 id;
}thread_args;



//
#define ALIGN64 64

pthread_barrier_t barrier1;

//
// void run_benchmark(const ascii *title, u64 n, u64 r, u64 sample);
void * run_benchmark(void * voidArgs);

//
int main(int argc, char **argv) {
    //
    srand(getpid());

    //
    if (argc < 4)
        return printf("usage: %s [n] [r] [core] \n", argv[0]), 1;

    // Number of array elements
    u64 n = atoll(argv[1]);

    // Number of kernel repetitions
    u64 r = atoll(argv[2]);
    
    // Numbre of cores
    u64 core = atoll(argv[3]);


    pthread_t id_threads[core];
    thread_args args[core];

    // Print header
    printf("%10s; %10s; %10s; %20s; %20s; \n",
           "core Id", "N", "r", "time ns", "GHz" );
    

    u64 c = core ;
    // for(u64 c = 1; c <= core - 1; c++){
        pthread_barrier_init(&barrier1, NULL, c + 1);
        for( u64 i = 0; i < c; i++){
            args[i].n = n;
            args[i].r = r;
            args[i].id = i;
            pthread_create(&id_threads[i], NULL, run_benchmark, &args[i] );
        } 
        
        pthread_barrier_wait(&barrier1);

        for( u64 i = 0; i < c; i++){
            pthread_join(id_threads[i], NULL );
        }
    //}

    //
    return 0;
}

//
// void run_benchmark(const ascii *title, u64 N, u64 r, u64 sample) {
void * run_benchmark( void * voidArgs) {
    

    thread_args * args = (thread_args *)voidArgs;
    u64 N = args->n;
    u64 r = args->r;
    u64 id = args->id;


    //
    f64 elapsed = 0.0;
    struct timespec t1, t2;

    pthread_barrier_wait(&barrier1);
    
    // heating
    for (u64 j = 0; j < 1000; j++){
        // printf("hello there\n");
        __asm__ volatile (
            "heat1:;\n"
            "dec %[_N];\n"
            "jnz heat1;\n"
            :
            : [_N] "r" (N)
            : "cc", "memory" );
    }

    //
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
    
    // do something while other threads finish their work
    for (u64 j = 0; j < 1000; j++){
            // printf("hello there\n");
            __asm__ volatile (
                "heat2:;\n"
                "dec %[_N];\n"
                "jnz heat2;\n"
                :
                : [_N] "r" (N)
                : "cc", "memory" );
        }

    // samples[i] = elapsed;
    f64 measure_freq = N / elapsed ;

    printf("%10llu; %10llu; %10llu; %20.5lf; %20.5lf; \n", 
        id, N, r, elapsed, measure_freq  );
    

   return 0; 

} 
