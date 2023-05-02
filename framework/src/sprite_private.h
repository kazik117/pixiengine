#ifndef _sprite_h_dd2fa68dfd9541f588712d877b54e67b_
#define _sprite_h_dd2fa68dfd9541f588712d877b54e67b_

#include <stdint.h>

struct sr_sprite_p
{
    uint32_t width;
    uint32_t height;
    struct sr_pixel* data;
};

#endif