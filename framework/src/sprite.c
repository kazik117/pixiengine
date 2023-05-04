#include <sr/pixel.h>
#include <sr/sprite.h>
#include "sprite_private.h"
#include <stdlib.h>

sr_sprite sr_sprite_create(uint32_t width, uint32_t height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    sr_sprite sprite = malloc(sizeof(struct sr_sprite_p));
    sprite->width = width;
    sprite->height = height;
    sprite->data = malloc(width * height * sizeof(struct sr_pixel));
    for (size_t i = 0; i < width * height; i++) {
        sprite->data[i] = (struct sr_pixel) { 25, 25, 25, 255 };
    }
    return sprite;
}

struct sr_pixel sr_sprite_get_pixel(sr_sprite sprite, uint32_t x, uint32_t y) {
    if (!sprite) return sr_default_pixel;
    if (x >= 0 && x < sprite->width && y >=0 && y < sprite->height) {
        return sprite->data[y * sprite->width + x];
    }
    return sr_default_pixel;
}

void sr_sprite_set_pixel(sr_sprite sprite, uint32_t x, uint32_t y, struct sr_pixel pixel) {
    if (!sprite) return;
    if (x >= 0 && x < sprite->width && y >= 0 && y < sprite->height) {
        sprite->data[y * sprite->width + x] = pixel;
    }
}

struct sr_pixel* sr_sprite_get_data(sr_sprite sprite) {
    if (!sprite) {
        return NULL;
    }
    return sprite->data;
}

void sr_sprite_destroy(sr_sprite sprite) {
    if (!sprite) return;
    if (sprite->data)
        free(sprite->data);
    free(sprite);
}
