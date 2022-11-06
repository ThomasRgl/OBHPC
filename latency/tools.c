
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//
#include "types.h"

void shuffle_pointer_adresses( void **restrict memblock, u64 size, int cycle_len)  {
//Shuffle pointer addresses

    for (u64 i = 0; i < size; i++) {
        memblock[i] = &memblock[i];
    }
    
    u64 ii;
    void * tmp;
    for (u64 i = 0; i < size; i++) {
        do{
            ii = rand()%size;
        } 
        while( ii == i);
        tmp = memblock[ii];
        memblock[ii] = memblock[i];
        memblock[i] = tmp;

    }
 

    // for (int i = size - 1; i >= 0; i--) {
    //     if (i < cycle_len)
    //         continue;
    //
    //     unsigned ii = (rand()%(i / cycle_len)) * cycle_len + (i % cycle_len);
    //
    //     void *tmp = memblock[i];
    //
    //     memblock[i] = memblock[ii];
    //     memblock[ii] = tmp;
    // }
}




//
void sort_f64(f64 *restrict a, u64 n) {
    for (u64 i = 0; i < n; i++)
        for (u64 j = i + 1; j < n; j++)
            if (a[i] > a[j]) {
                f64 tmp = a[i];

                a[i] = a[j];
                a[j] = tmp;
            }
}

//
f64 mean_f64(f64 *restrict a, u64 n) {
    f64 m = 0.0;

    for (u64 i = 0; i < n; i++)
        m += a[i];

    m /= (f64)n;

    return m;
}

//
f64 stddev_f64(f64 *restrict a, u64 n) {
    f64 d = 0.0;
    f64 m = mean_f64(a, n);

    for (u64 i = 0; i < n; i++)
        d += (a[i] - m) * (a[i] - m);

    d /= (f64)(n - 1);

    return sqrt(d);
}
