#include <sr/app.h>
#include <sr/pixel.h>
#include <sr/sprite.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool on_user_create();
bool on_user_update(sr_app_t, double);

int main() {
    struct sr_app_args args = { "SAMPLE Application", on_user_create, on_user_update };
    sr_app_t app = sr_app_create(&args);
    if (sr_app_window(app, 1280, 720, 1, 1) == E_OK) {
        sr_app_start(app);
    }
    sr_app_destroy(app);
    return 0;
}

bool on_user_create() {
    srand(time(NULL));
    return true;
}

bool on_user_update(sr_app_t app, double elapsedTime) {
    for (int i = 0; i < sr_app_width(app); i++) {
        for (int j = 0; j < sr_app_height(app); j++) {
            sr_app_draw(app, i, j, (struct sr_pixel) { { rand() % 255, rand() % 255, rand() % 255, 255 } });
        }
    }
    return true;
}
