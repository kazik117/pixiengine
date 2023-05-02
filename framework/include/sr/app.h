#ifndef _app_h_3de41581409849e9be370ea5e2a78b04_
#define _app_h_3de41581409849e9be370ea5e2a78b04_

#include <sr/pixel.h>
#include <sr/error.h>

#include <stdbool.h>
#include <stdint.h>

#ifndef NDEBUG
#define PROFILER_ENABLED
#endif

typedef struct sr_app_p* sr_app_t;

struct sr_app_args
{
    const char* name;
    bool (*on_create)(sr_app_t);
    bool (*on_update)(sr_app_t,double);
    bool (*on_destroy)(sr_app_t);
#ifdef PROFILER_ENABLED
    bool is_benchmark;
    uint32_t benchmark_repeat_count;
#endif
};

sr_app_t sr_app_create(struct sr_app_args *args);
void sr_app_destroy(sr_app_t app);

sr_error_t sr_app_window(sr_app_t app, uint16_t width, uint16_t height, uint16_t pixel_width, uint16_t pixel_height);
sr_error_t sr_app_start(sr_app_t app);

void sr_app_draw(sr_app_t app, uint16_t x, uint16_t y, struct sr_pixel color);

uint32_t sr_app_width(sr_app_t app);
uint32_t sr_app_height(sr_app_t app);

#endif