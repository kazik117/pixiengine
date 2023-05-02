#include <sr/app.h>
#include <sr/pixel.h>
#include <stdio.h>
#include <stdlib.h>
#include "line.h"

const struct sr_pixel white = { 255, 255, 255, 255 };
const struct sr_pixel black = { 0, 0, 0, 255 };
const struct sr_pixel red = { 255, 0, 0, 255 };
const struct sr_pixel blue = { 0, 0, 255, 255 };
const struct sr_pixel green = { 0, 255, 0, 255 };
const struct sr_pixel yellow = { 255, 255, 0, 255 };

bool on_create(sr_app_t app);
bool on_update(sr_app_t app, double elapsedTime);

int main() {
    struct sr_app_args params = { "Tiny renderer", on_create, on_update };
    sr_app_t app = sr_app_create(&params);
    if (sr_app_window(app, 100, 100, 4, 4) == E_OK) {
        sr_app_start(app);
    }
    sr_app_destroy(app);
    return 0;
}

bool on_create(sr_app_t app) {
    return true;
}

bool on_update(sr_app_t app, double elapsedTime) {
    line(14, 21, 81, 41, app, white); 
    line(20, 13, 40, 80, app, red); 
    line(80, 40, 13, 20, app, green);
    return true;
}
