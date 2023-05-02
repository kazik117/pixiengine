#ifndef _app_h_bed4780d5cf04175a911b357c455e875_
#define _app_h_bed4780d5cf04175a911b357c455e875_

#include <sr/app.h>
#include <sr/sprite.h>
#include <GLFW/glfw3.h>

struct sr_app_p
{
    struct sr_app_args args;
    uint16_t width;
    uint16_t height;
    uint16_t pixel_w;
    uint16_t pixel_h;
    sr_sprite draw_target;
    bool atomActive;
    GLFWwindow* window;
    void* buffer;
};

void* app_engine(void*);

#endif