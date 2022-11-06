//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//
#include "types.h"

//
#include "tools.h"

//
#include "kernels.h"

//
#define ALIGN64 64



//
int main(int argc, char **argv) {
    //
    srand(getpid());


    // Number of array elements
    u64 n = 16;
    
    
    // Calculate the size of a single matrix
    u64 size = (sizeof(f64) * n * n);


    //
    f64 *restrict a = aligned_alloc(ALIGN64, size);
    f64 *restrict b = aligned_alloc(ALIGN64, size);
    f64 *restrict c = aligned_alloc(ALIGN64, size);

    //
    init_f64(a, n, 'r');
    init_f64(b, n, 'r');
    init_f64(c, n, 'z');
   

    printf("IJK\n");
    dgemm_ijk(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    printf("IKJ\n");
    dgemm_ikj(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    printf("IEX\n");
    dgemm_iex(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    // printf("TRANS\n");
    // dgemm_trans(a, b, c, n);
    // print_f64(c, n);
    // init_f64(c, n, 'z');
    //
    printf("UNROLL4\n");
    dgemm_unroll4(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    printf("UNROLL8\n"); 
    dgemm_unroll8(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    printf("UNROLL16\n"); 
    dgemm_unroll16(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    printf("CACHE_LINE\n");
    dgemm_CL(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');

    // run_benchmark("CACHE_LINE2", dgemm_CL2, n, r);
    printf("CBLAS\n");
    dgemm_cblas(a, b, c, n);
    print_f64(c, n);
    init_f64(c, n, 'z');





    //
    free(a);
    free(b);
    free(c);



}


