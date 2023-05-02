#ifndef _pixel_h_5142ef44e3264354ab56edaf801f712b_
#define _pixel_h_5142ef44e3264354ab56edaf801f712b_

#include <stdint.h>

struct sr_pixel
{
    union
    {
        struct
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };
        
    };
};


#endif