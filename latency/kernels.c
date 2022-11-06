
//
#include "types.h"

//from http://193.51.33.67/public_html/arm_intel_amd/chap1/
void ** pointer_chasing(u64 iterations, void *restrict memblock){
//void ** pointer_chasing(int iterations, void ** memblock){
    void **restrict p = &memblock[0];
    
    for (u64 i = iterations; i; i--) {
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
        p = *(void **)p;
    }

    return p;
}

