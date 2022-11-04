//
#if defined(__INTEL_COMPILER)
#include <mkl.h>
#else
//#include <cblas.h>
#include <cblas.h>
#endif

//
#include "types.h"



// Baseline - naive implementation
void dgemm_ijk(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    for (u64 i = 0; i < n; i++)
        for (u64 j = 0; j < n; j++)
            for (u64 k = 0; k < n; k++)
                c[i * n + j] += a[i * n + k] * b[k * n + j];
}

// First optimization (loop interchange)
void dgemm_ikj(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    for (u64 i = 0; i < n; i++)
        for (u64 k = 0; k < n; k++)
            for (u64 j = 0; j < n; j++)
                c[i * n + j] += a[i * n + k] * b[k * n + j];
}

// Second optimization (loop interchange + invariant extraction)
void dgemm_iex(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    for (u64 i = 0; i < n; i++) {
        for (u64 k = 0; k < n; k++) {
            const f64 _a_ = a[i * n + k];

            for (u64 j = 0; j < n; j++)
                c[i * n + j] += _a_ * b[k * n + j];
        }
    }
}

void dgemm_trans(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    
    u64 i, j, k = 0;
    f64 tmp = 0;
    for ( i = 0; i < n; ++ i)
        for ( j = 0; j <= i; ++ j){
            tmp = b[ i * n + j];
            b[i * n + j] = b[j * n + i];
            b[j * n + i] = tmp;
        }

    for ( i = 0; i < n; ++ i)
        for ( j = 0; j < n; ++ j)
            for ( k = 0; k < n; ++ k)
                c [ i * n + j ] += a [i * n + k] * b [ j * n + k ];
//
}



void dgemm_unroll4(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
#define UNROLL4 4

    for (u64 i = 0; i < n; i++) {
        for (u64 k = 0; k < n; k++) {
            const f64 _a_ = a[i * n + k];

            u64 modulo = n % UNROLL4;
            for (u64 j = 0; j < n - modulo; j += UNROLL4) {
                c[i * n + j] += _a_ * b[k * n + j];
                c[i * n + j + 1] += _a_ * b[k * n + j + 1];
                c[i * n + j + 2] += _a_ * b[k * n + j + 2];
                c[i * n + j + 3] += _a_ * b[k * n + j + 3];
            }

            for (u64 j = n - modulo; j < n; j ++) {
                c[i * n + j] += _a_ * b[k * n + j];
            }

        }
    }
}

//
void dgemm_unroll8(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
#define UNROLL8 8

    for (u64 i = 0; i < n; i++) {
        for (u64 k = 0; k < n; k++) {
            const f64 _a_ = a[i * n + k];

            u64 modulo = n % UNROLL8;
            for (u64 j = 0; j < n - modulo; j += UNROLL8) {
                c[i * n + j] += _a_ * b[k * n + j];
                c[i * n + j + 1] += _a_ * b[k * n + j + 1];
                c[i * n + j + 2] += _a_ * b[k * n + j + 2];
                c[i * n + j + 3] += _a_ * b[k * n + j + 3];
                c[i * n + j + 4] += _a_ * b[k * n + j + 4];
                c[i * n + j + 5] += _a_ * b[k * n + j + 5];
                c[i * n + j + 6] += _a_ * b[k * n + j + 6];
                c[i * n + j + 7] += _a_ * b[k * n + j + 7];
            }
 
            for (u64 j = n - modulo; j < n; j ++) {
                c[i * n + j] += _a_ * b[k * n + j];
            }

        }
    }
}

//
void dgemm_unroll16(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
#define UNROLL16 16

    for (u64 i = 0; i < n; i++) {
        for (u64 k = 0; k < n; k++) {
            const f64 _a_ = a[i * n + k];

            u64 modulo = n % UNROLL16;
            for (u64 j = 0; j < n - modulo; j += UNROLL16) {
                c[i * n + j] += _a_ * b[k * n + j];
                c[i * n + j + 1] += _a_ * b[k * n + j + 1];
                c[i * n + j + 2] += _a_ * b[k * n + j + 2];
                c[i * n + j + 3] += _a_ * b[k * n + j + 3];
                c[i * n + j + 4] += _a_ * b[k * n + j + 4];
                c[i * n + j + 5] += _a_ * b[k * n + j + 5];
                c[i * n + j + 6] += _a_ * b[k * n + j + 6];
                c[i * n + j + 7] += _a_ * b[k * n + j + 7];
                c[i * n + j + 8] += _a_ * b[k * n + j + 8];
                c[i * n + j + 9] += _a_ * b[k * n + j + 9];
                c[i * n + j + 10] += _a_ * b[k * n + j + 10];
                c[i * n + j + 11] += _a_ * b[k * n + j + 11];
                c[i * n + j + 12] += _a_ * b[k * n + j + 12];
                c[i * n + j + 13] += _a_ * b[k * n + j + 13];
                c[i * n + j + 14] += _a_ * b[k * n + j + 14];
                c[i * n + j + 15] += _a_ * b[k * n + j + 15];
            }
        
            for (u64 j = n - modulo; j < n; j ++) {
                c[i * n + j] += _a_ * b[k * n + j];
            }
}
    }
}

//
#define CLS  64
#define SM (CLS / sizeof (f64))
//

// #define L2 64
// #define SM 32
// #define L3 16
//

void dgemm_CL(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    f64 * ra = NULL;
    f64 * rb = NULL;
    f64 * rc = NULL;
    
    u64 i, j, k, i2, k2, j2 = 0;
    for( i = 0; i < n; i += SM )
        for( j = 0; j < n; j +=SM )
            for( k= 0; k < n; k += SM)

                for( i2 = 0, rc = &c[i * n + j], ra = &a[i * n + k]; i2 < SM; ++i2, rc += n, ra += n)
                    for( k2 = 0, rb = &b[k * n + j]; k2 < SM; ++k2, rb += n)
                        for( j2 = 0; j2 < SM; ++j2)
                            rc[j2] += ra[k2] * rb[j2];
}



// void dgemm_CL2(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
//     f64 * ra = NULL;
//     f64 * rb = NULL;
//     f64 * rc = NULL;
//     
//     u64 i, j, k, i2, k2, j2 = 0;
//     for( i = 0; i < n; i += L2 )
//         for( j = 0; j < n; j +=SM )
//             for( k= 0; k < n; k += L3)
//
//                 for( i2 = 0, rc = &c[i * n + j], ra = &a[i * n + k]; i2 < L2; ++i2, rc += n, ra += n)
//                     for( k2 = 0, rb = &b[k * n + j]; k2 < L3; ++k2, rb += n)
//                         for( j2 = 0; j2 < SM; ++j2)
//                             rc[j2] += ra[k2] * rb[j2];
//
// }


void dgemm_cblas(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, a, n,
                b, n, 0.0, c, n);
}
