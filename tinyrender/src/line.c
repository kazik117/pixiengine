#include <sr/pixel.h>
#include <sr/app.h>
#include "line.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>

void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, sr_app_t app, struct sr_pixel color) {
    bool steep = false;
    if (abs(x0 - x1) < abs(y0 - y1)) {
        swapi(&x0, &y0);
        swapi(&x1, &y1);
        steep = true;
    }
    if (x0 > x1) {
        swapi(&x0, &x1);
        swapi(&y0, &y1);
    }
    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t derror = abs(dy) * 2;
    int32_t error = 0;
    int32_t y = y0;
    const int32_t ymove = (y1 > y0) ? 1 : -1;
    if (steep) {
        for (int x = x0; x <= x1; x++) {
            sr_app_draw(app, y, x, color);
            error += derror;
            if (error > dx) {
                y += ymove;
                error -= dx * 2;
            }
        }
    }
    else {
        for (int x = x0; x <= x1; x++) {
            sr_app_draw(app, x, y, color);
            error += derror;
            if (error > dx) {
                y += ymove;
                error -= dx * 2;
            }
        }
    }
}
