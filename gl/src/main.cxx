#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void cleanupResources();
void framebufferResize(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void keyCallback(GLFWwindow*, int, int, int, int);

int32_t fillType = GL_FILL;

int main(int argc, char **argv) {
    atexit(cleanupResources);
    std::cout << "Starting OpengGL exampels application" << std::endl;

    if (!glfwInit()) {
        std::cerr << "Initialization GLFW failed." << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    int width = 800, height = 600;

    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL 3.3", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Initialization window failed" << std::endl;
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Loading GLAD failed" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, framebufferResize);
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetKeyCallback(window, keyCallback);
    glViewport(0, 0, width, height);
    glClearColor(.2f, .3f, .3f, 1.f);

    const char  *vertex_shader = R"XX(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.);
}
    )XX";

    uint32_t vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);
    int32_t success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorBuffer[512];
        glGetShaderInfoLog(vs, 512, nullptr, errorBuffer);
        std::cerr << "Failed compile vertex shader: " << errorBuffer << std::endl;
    }

    const char *fragment_shader = R"XX(
#version 330 core
out vec4 fragColor;

void main() {
    fragColor = vec4(1., .4, 0.4, 1.);
}
    )XX";

    uint32_t fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorBuffer[512];
        glGetShaderInfoLog(fs, 512, nullptr, errorBuffer);
        std::cerr << "Failed compile fragment shader: " << errorBuffer << std::endl;
    }

    uint32_t program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char errorBuffer[512];
        glGetProgramInfoLog(program, 512, nullptr, errorBuffer);
        std::cerr << "Failed link program: " << errorBuffer << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    float vertices[] = {
        -.5,  -.5, .0,
         .5,  -.5, .0,
        .5,   .5, .0,
        -.5,  .5, .0,
    };
    uint32_t indices[] = {
        2, 3, 1,
        1, 3, 0
    };

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint32_t ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        glUseProgram(program);
        glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        if (fillType == GL_FILL) {
            fillType = GL_LINE;
        } else if (fillType == GL_LINE) {
            fillType = GL_FILL;
        }
        glPolygonMode(GL_FRONT_AND_BACK, fillType);
    }
}

void cleanupResources() {
    glfwTerminate();
    std::cout << "Shutdown cleanup resources" << std::endl;
}

void framebufferResize(GLFWwindow *window, int width, int height) {
    std::cout << "Resize window [" << width << "x" << height << "]" << std::endl;
    glViewport(0, 0, width, height);
}