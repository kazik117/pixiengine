#include "app_private.h"
#include "platform_private.h"
#include <stdio.h>

void window_error(int code, const char* description) {
    fprintf(stderr, "Window error[%d]: %s", code, description);
}

void window_close(GLFWwindow* window) {
    sr_app_t app = (sr_app_t) glfwGetWindowUserPointer(window);
    app->atomActive = false;
}

sr_error_t window_create(sr_app_t app) {
    if (!app) return E_BADPTR;
    glfwSetErrorCallback(window_error);
    if (!glfwInit()) {
        glfwSetErrorCallback(NULL);
        return E_INIT;
    }
    // TODO set hints to window
    uint32_t width = app->width * app->pixel_w, height = app->height * app->pixel_h;
    GLFWwindow* window = glfwCreateWindow(width, height, app->args.name, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        glfwSetErrorCallback(NULL);
        return E_WINCREAT;
    }
    app->window = window;
    glfwSetWindowUserPointer(app->window, app);
    glfwSetWindowCloseCallback(app->window, window_close);
    return E_OK;
}

void window_destroy(sr_app_t app) {
    if (!app) return;
	if (app->window) {
		glfwSetWindowCloseCallback(app->window, NULL);
		glfwDestroyWindow(app->window);
	}
    glfwTerminate();
    glfwSetErrorCallback(NULL);
    app->window = NULL;
}

void window_set_title(sr_app_t app, const char* title) {
    if (!app || !title) return;
    glfwSetWindowTitle(app->window, title);
}

void window_make_context(sr_app_t app) {
    if (!app || !app->window) return;
    glfwMakeContextCurrent(app->window);
    glfwSwapInterval(0);
}

void window_poll_events(sr_app_t app) {
    if (!app) return;
    glfwPollEvents();
}

double window_get_time(sr_app_t app) {
    if (!app) return 0;
    return glfwGetTime();
}

void window_renderer_prepare(sr_app_t app) {
    if (!app) return;
    int32_t frameWidth, frameHeight;
    glfwGetFramebufferSize(app->window, &frameWidth, &frameHeight);

    glViewport(0, 0, frameWidth, frameHeight);
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);

    uint32_t buffer;
    app->buffer = &buffer;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, (GLuint*)app->buffer);
    glBindTexture(GL_TEXTURE_2D, *(GLuint*)app->buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void window_renderer_frame_start(sr_app_t app) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_renderer_draw(sr_app_t app) {
    if (!app) return;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, app->width, app->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sr_sprite_get_data(app->draw_target));

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f,  1.0f, 0.0f);
    glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(1.0, 1.0); glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();

    glfwSwapBuffers(app->window);
}

void window_renderer_release(sr_app_t app) {
    if (!app) return;
    glDeleteTextures(1, (GLuint*)app->buffer);
}