#include <input.h>

Input::Input(Camera *camera, Window *window) : camera(camera), window(window) {
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window->getWindow(), this);
    glfwSetCursorPosCallback(window->getWindow(), Input::mouse_callback);
}

void Input::processInput() {
    for (const auto &[key, action] : KEYS) {
        if (glfwGetKey(window->getWindow(), key) == GLFW_PRESS && action()) last_key = key;
    }
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
