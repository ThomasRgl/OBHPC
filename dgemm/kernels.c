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

            for (u64 j = 0; j < n; j += UNROLL8) {
                c[i * n + j] += _a_ * b[k * n + j];
                c[i * n + j + 1] += _a_ * b[k * n + j + 1];
                c[i * n + j + 2] += _a_ * b[k * n + j + 2];
                c[i * n + j + 3] += _a_ * b[k * n + j + 3];
                c[i * n + j + 4] += _a_ * b[k * n + j + 4];
                c[i * n + j + 5] += _a_ * b[k * n + j + 5];
                c[i * n + j + 6] += _a_ * b[k * n + j + 6];
                c[i * n + j + 7] += _a_ * b[k * n + j + 7];
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

            for (u64 j = 0; j < n; j += UNROLL16) {
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
        }
    }
}


void dgemm_cblas(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, a, n,
                b, n, 0.0, c, n);
}