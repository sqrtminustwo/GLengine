#ifndef INPUT_H
#define INPUT_H

#include <camera.h>
#include <window.h>
#include <GLFW/glfw3.h>
#include <map>
#include <functional>

class Input {
  public:
    Input(Camera *camera, Window *window);

    void processInput();

    static void mouse_callback(GLFWwindow *glfwWindow, double xposIn, double yposIn) {
        auto *input = static_cast<Input *>(glfwGetWindowUserPointer(glfwWindow));
        if (!input) return;

        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (input->firstMouse) {
            input->lastX = xpos;
            input->lastY = ypos;
            input->firstMouse = false;
        }

        float xoffset = xpos - input->lastX;
        float yoffset = input->lastY - ypos;

        input->lastX = xpos;
        input->lastY = ypos;

        input->camera->processMouseMovement(xoffset, yoffset);
    }

  private:
    Camera *camera;
    Window *window;
    float lastX = window->getWidth() / 2.0f;
    float lastY = window->getHeight() / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    int last_key = -1;
    int input_mode = GLFW_CURSOR_DISABLED;

    const std::map<int, std::function<bool()>> KEYS{
        {GLFW_KEY_TAB,
         [this]() -> bool {
             if (last_key == GLFW_KEY_TAB) return false;
             camera->change_fps();
             last_key = GLFW_KEY_TAB;
             return true;
         }},
        {GLFW_KEY_ESCAPE,
         [this]() -> bool {
             if (last_key == GLFW_KEY_ESCAPE) return false;
             input_mode = input_mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
             glfwSetInputMode(window->getWindow(), GLFW_CURSOR, input_mode);
             last_key = GLFW_KEY_ESCAPE;
             return true;
         }},
        {GLFW_KEY_W, [this]() -> bool { return camera->processKeyboard(FORWARD, deltaTime); }},
        {GLFW_KEY_S, [this]() -> bool { return camera->processKeyboard(BACKWARD, deltaTime); }},
        {GLFW_KEY_A, [this]() -> bool { return camera->processKeyboard(LEFT, deltaTime); }},
        {GLFW_KEY_D, [this]() -> bool { return camera->processKeyboard(RIGHT, deltaTime); }},
        {GLFW_KEY_SPACE, [this]() -> bool { return camera->processKeyboard(UP, deltaTime); }},
        {GLFW_KEY_LEFT_CONTROL, [this]() -> bool { return camera->processKeyboard(DOWN, deltaTime); }},
    };
};

#endif
