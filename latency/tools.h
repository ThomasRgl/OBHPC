//
#pragma once

//
#include "types.h"

//
void shuffle_pointer_adresses( void **restrict memblock, u64 size, int cycle_len);
void sort_f64(f64 *restrict a, u64 n);
f64 mean_f64(f64 *restrict a, u64 n);
f64 stddev_f64(f64 *restrict a, u64 n);
