#ifndef _utils_h_a443f14b272245ec90d5f0cf08cb3a3e_
#define _utils_h_a443f14b272245ec90d5f0cf08cb3a3e_

#include <stdint.h>

static inline void swapi(uint16_t* lhs, uint16_t* rhs) {
    uint16_t tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

#endif