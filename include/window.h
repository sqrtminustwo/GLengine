#ifndef WINDOW_H
#define WINDOW_H

#include <glad.h>
#include <GLFW/glfw3.h>
#include <tuple>

using rgba = std::tuple<float, float, float, float>;

class Window {

  public:
    Window(unsigned int WIDTH, unsigned int HEIGHT);
    Window(unsigned int WIDTH, unsigned int HEIGHT, rgba color);

    void setColor(rgba color) { this->color = normalizeRGBA(color); }

    void clearScreen();

    GLFWwindow *getWindow() { return window; }
    unsigned int getWidth() { return WIDTH; }
    unsigned int getHeight() { return HEIGHT; }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

  private:
    GLFWwindow *window;
    const unsigned int WIDTH = 1280;
    const unsigned int HEIGHT = 1000;
    rgba color;

    rgba normalizeRGBA(rgba color);
};

#endif
