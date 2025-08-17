#include <glad.h>
#include <window.h>
#include <iostream>

Window::Window(unsigned int WIDTH, unsigned int HEIGHT) : WIDTH(WIDTH), HEIGHT(HEIGHT) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "GLengine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
}

Window::Window(unsigned int WIDTH, unsigned int HEIGHT, rgba color) : Window(WIDTH, HEIGHT) { setColor(color); }

void Window::clearScreen() {
    auto [r, g, b, a] = color;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

rgba Window::normalizeRGBA(rgba color) {
    auto [r, g, b, a] = color;
    return std::tuple(r / 255.0f, g / 255.0f, b / 255.0f, a);
}
