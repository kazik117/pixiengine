#ifndef _sprite_h_7116a16064784f4e8de3cc81db013a10_
#define _sprite_h_7116a16064784f4e8de3cc81db013a10_

#include <sr/pixel.h>
#include <stdint.h>

typedef struct sr_sprite_p* sr_sprite;

sr_sprite sr_sprite_create(uint32_t width, uint32_t height);
void sr_sprite_destroy(sr_sprite sprite);

struct sr_pixel sr_sprite_get_pixel(sr_sprite sprite, uint32_t x, uint32_t y);
void sr_sprite_set_pixel(sr_sprite sprite, uint32_t x, uint32_t y, struct sr_pixel pixel);
struct sr_pixel* sr_sprite_get_data(sr_sprite sprite);

#endif