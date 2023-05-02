#include <sr/pixel.h>
#include <sr/app.h>
#include "line.h"
#include "utils.h"
#include <stdlib.h>

void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, sr_app_t app, struct sr_pixel color) {
    bool steep = false;
    if (abs(x0-x1) < abs(y0-y1)) {
        swapi(&x0, &y0);
        swapi(&x1, &y1);
        steep = true;
    }
    if (x0 > x1) {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
    }
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        uint16_t y = y0 * (1. - t) + y1 * t;
        if (steep) {
            sr_app_draw(app, y, x, color);
        } else {
            sr_app_draw(app, x, y, color);
        }
    }
}
