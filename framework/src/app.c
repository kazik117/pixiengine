#include <sr/app.h>
#include <sr/pixel.h>
#include <sr/sprite.h>
#include "app_private.h"
#include "sprite_private.h"
#include "platform_private.h"

#include <stdio.h>
#include <stdlib.h>

sr_app_t sr_app_create(struct sr_app_args *args) {
    sr_app_t result = calloc(1, sizeof(struct sr_app_p));
    if (result == NULL) {
        return NULL;
    }
    result->args = *args;
    return result;
}

sr_error_t sr_app_window(sr_app_t app, uint16_t width, uint16_t height, uint16_t pixel_width, uint16_t pixel_height) {
    if (!app) return E_BADPTR;
    app->width = width;
    app->height = height;
    app->pixel_w = pixel_width;
    app->pixel_h = pixel_height;
    app->draw_target = sr_sprite_create(width, height);
    if (!app->draw_target) {
        return E_INIT;
    }
    return E_OK;
}

sr_error_t sr_app_start(sr_app_t app) {
    if (!app) return E_BADPTR;
    app->atomActive = true;
    sr_error_t result;
    if ((result = window_create(app)) != E_OK) {
        return result;
    }
    app_engine(app);
    return E_OK;
}

void sr_app_destroy(sr_app_t app) {
    if (!app) return;
    sr_sprite_destroy(app->draw_target);
    window_destroy(app);
    free(app);
}

void sr_app_draw(sr_app_t app, uint16_t x, uint16_t y, struct sr_pixel color) {
    if (!app) return;
    sr_sprite_set_pixel(app->draw_target, x, y, color);
}

uint32_t sr_app_width(sr_app_t app) {
    if (!app) return 0;
    return app->width;
}

uint32_t sr_app_height(sr_app_t app) {
    if (!app) return 0;
    return app->height;
}

/* ========================================================================
    PRIVATE API SECTION
*/
#pragma region PrivateAPI

void* app_engine(void* input) {
    sr_app_t app = (sr_app_t)input;

    window_make_context(app);
    window_renderer_prepare(app);

    if (!app->args.on_create(app)) {
        app->atomActive = false;
    }

    double tp1 = window_get_time(app);
    double tp2 = window_get_time(app);

    char title[256] = {0};
    size_t titleLength = sizeof(title)/sizeof(title[0]);
    snprintf(title, titleLength, "Simple Renderer :: %s - %3.2f FPS", app->args.name, 0.f);
    window_set_title(app, title);

#ifdef PROFILER_ENABLED
    uint32_t repeat = 0;
#endif
    //TODO: Implement benchmarking to max iterations
    while (app->atomActive) {
        window_poll_events(app);
        tp2 = window_get_time(app);
        double elapsedTime = tp2 - tp1;
        tp1 = tp2;
        // TODO: handle input

        window_renderer_frame_start(app);
        if (!app->args.on_update(app, elapsedTime)) {
            app->atomActive = false;
        }
        window_renderer_draw(app);

        static double fpsTime = 0;
        fpsTime += elapsedTime;
        if (fpsTime >= 0.1) {
            snprintf(title, titleLength, "Simple Renderer :: %s - %3.2f FPS", app->args.name, 1.f / elapsedTime);
            window_set_title(app, title);
            fpsTime = 0;
        }
    #ifdef PROFILER_ENABLED
        if (app->args.benchmark_repeat_count > 0) {
            repeat++;
            if (repeat >= app->args.benchmark_repeat_count) {
                break;
            }
        }
    #endif
    }

    window_renderer_release(app);
    return NULL;
}

#pragma endregion