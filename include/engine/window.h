#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <tuple>

using rgba = std::tuple<float, float, float, float>;

class Window {

  public:
    Window(const unsigned int WIDTH, const unsigned int HEIGHT);
    Window(const unsigned int WIDTH, const unsigned int HEIGHT, const rgba color);

    void setColor(const rgba color) { this->color = normalizeRGBA(color); }

    void clearScreen();

    GLFWwindow *getWindow() const { return window; }
    unsigned int getWidth() const { return WIDTH; }
    unsigned int getHeight() const { return HEIGHT; }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

  private:
    GLFWwindow *window;
    const unsigned int WIDTH = 1280;
    const unsigned int HEIGHT = 1000;
    rgba color;

    rgba normalizeRGBA(rgba color) const;
};

#endif
