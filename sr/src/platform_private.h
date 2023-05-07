#ifndef _platform_h_a276e1043803450784eacbedbf0e6037_
#define _platform_h_a276e1043803450784eacbedbf0e6037_

#include <sr/app.h>
#include <sr/error.h>

sr_error_t window_create(sr_app_t app);
void window_destroy(sr_app_t app);

void window_set_title(sr_app_t app, const char* title);
void window_make_context(sr_app_t app);
void window_poll_events(sr_app_t app);
double window_get_time(sr_app_t app);
void window_renderer_prepare(sr_app_t app);
void window_renderer_frame_start(sr_app_t app);
void window_renderer_draw(sr_app_t app);
void window_renderer_release(sr_app_t app);

#endif