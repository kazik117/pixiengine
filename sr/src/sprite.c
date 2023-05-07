#include <sr/pixel.h>
#include <sr/sprite.h>
#include "sprite_private.h"
#include <stdlib.h>

sr_sprite sr_sprite_create(uint16_t width, uint16_t height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    sr_sprite sprite = malloc(sizeof(struct sr_sprite_p));
    if (sprite == NULL) {
        return NULL;
    }
    sprite->width = width;
    sprite->height = height;
    uint32_t size = width * height;
    sprite->data = malloc(size * sizeof(struct sr_pixel));
    if (sprite->data == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        *(sprite->data + i) = (struct sr_pixel) { 25, 25, 25, 255 };
    }
    return sprite;
}

struct sr_pixel sr_sprite_get_pixel(sr_sprite sprite, uint16_t x, uint16_t y) {
    if (!sprite) return sr_default_pixel;
    if (x >= 0 && x < sprite->width && y >=0 && y < sprite->height) {
        return sprite->data[y * sprite->width + x];
    }
    return sr_default_pixel;
}

void sr_sprite_set_pixel(sr_sprite sprite, uint16_t x, uint16_t y, struct sr_pixel pixel) {
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
