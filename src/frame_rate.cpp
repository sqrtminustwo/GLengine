#include <frame_rate.h>
#include <GLFW/glfw3.h>
#include <iostream>

FrameRate::FrameRate() { last_time = glfwGetTime(); }

void FrameRate::stat() {
    frames++;
    double current_time = glfwGetTime();
    if (current_time - last_time >= 1) {
        std::cout << frames << "\n";
        frames = 0;
        last_time = current_time;
    }
}
