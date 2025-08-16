#include <window.h>
#include <camera.h>
#include <cube.h>
#include <input.h>
#include <shader.h>
#include <stats.h>

int main() {

    Window window(1280, 1000, std::tuple(0, 0, 0, 0.7));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shape_shader(
        PROJECT_DIR "/resources/shaders/shape/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/fragment_shader.glsl"
    );

    std::vector<Cube *> cubes;

    Cube cube1{};
    cubes.push_back(&cube1);

    Cube cube2{cube1};
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, glm::vec3(-2.0f, -2.0f, 1.0f));
    cube2.setTranslationMatrix(translate);
    cubes.push_back(&cube2);

    char background[] = PROJECT_DIR "/resources/textures/yellow.png";
    char frame[] = PROJECT_DIR "/resources/textures/frame4.png";
    shape_shader.loadTexture(background);
    shape_shader.loadTexture(frame);
    shape_shader.setProjectionMatrix(cube1.getProjectionMatrix());

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shape_shader.setScaleMatrix(scaleDown);

    Stats stats{};
    stats.start(); // End is defined in class destructor

    while (!glfwWindowShouldClose(window.getWindow())) {
        stats.updateFps();

        input.processInput();

        window.clearScreen();

        shape_shader.use();

        cube1.setModelMatrix(
            glm::rotate(cube1.getModelMatrix(), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f))
        );
        shape_shader.setViewMatrix(camera.getViewMatrix());

        for (Cube *cube : cubes) {
            shape_shader.setModelMatrix(cube->getModelMatrix());
            shape_shader.setProjectionMatrix(cube->getProjectionMatrix());
            shape_shader.setTranslationMatrix(cube->getTranslationMatrix());
            cube->drawShape();
        }

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    for (Cube *cube : cubes) cube->destruct();
    glfwTerminate();
    return 0;
}

// #include <chrono>                 // for operator""s, chrono_literals
// #include <cmath>                  // for sin
// #include <ftxui/dom/elements.hpp> // for graph, operator|, separator, color, Element, vbox, flex, inverted,
// operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT #include <ftxui/screen/screen.hpp> // for Full, Screen
// #include <functional>              // for ref, reference_wrapper
// #include <iostream>                // for cout, ostream
// #include <memory>                  // for shared_ptr
// #include <string>                  // for operator<<, string
// #include <thread>                  // for sleep_for
// #include <vector>                  // for vector
//
// #include "ftxui/dom/node.hpp"     // for Render
// #include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui
//
// class Graph {
//   public:
//     std::vector<int> operator()(int width, int height) const {
//         std::vector<int> output(width);
//         for (int i = 0; i < width; ++i) {
//             float v = 0;
//             v += 0.1f * sin((i + shift) * 0.1f);       // NOLINT
//             v += 0.2f * sin((i + shift + 10) * 0.15f); // NOLINT
//             v += 0.1f * sin((i + shift) * 0.03f);      // NOLINT
//             v *= height;                               // NOLINT
//             v += 0.5f * height;                        // NOLINT
//             output[i] = static_cast<int>(v);
//         }
//         return output;
//     }
//     int shift = 0;
// };
//
// std::vector<int> triangle(int width, int height) {
//     std::vector<int> output(width);
//     for (int i = 0; i < width; ++i) { output[i] = i % (height - 4) + 2; }
//     return output;
// }
//
// int main() {
//     using namespace ftxui;
//     using namespace std::chrono_literals;
//
//     Graph my_graph;
//
//     std::string reset_position;
//     while (true) {
//         auto document = hbox({graph(std::ref(my_graph)) | color(Color::DarkKhaki)});
//
//         document |= border;
//
//         const int min_width = 40;
//         document |= size(HEIGHT, GREATER_THAN, min_width);
//
//         auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
//         Render(screen, document);
//         std::cout << reset_position;
//         screen.Print();
//         reset_position = screen.ResetPosition();
//
//         const auto sleep_time = 0.03s;
//         std::this_thread::sleep_for(sleep_time);
//         my_graph.shift++;
//     }
//
//     return 0;
// }

// #include <memory> // for shared_ptr, allocator, __shared_ptr_access
//
// #include "ftxui/component/captured_mouse.hpp" // for ftxui
// #include "ftxui/component/component.hpp" // for Renderer, ResizableSplitBottom, ResizableSplitLeft,
// ResizableSplitRight, ResizableSplitTop #include "ftxui/component/component_base.hpp"     // for ComponentBase
// #include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
// #include "ftxui/dom/elements.hpp"                 // for Element, operator|, text, center, border
//
// using namespace ftxui;
//
// int main() {
//     auto screen = ScreenInteractive::Fullscreen();
//
//     auto left = Renderer([] { return text("Left") | center; });
//     auto right = Renderer([] { return text("right") | center; });
//
//     int left_size = 20;
//     int right_size = 20;
//
//     auto container = ResizableSplitRight(right, left, &right_size);
//
//     auto renderer = Renderer(container, [&] { return container->Render() | border; });
//
//     screen.Loop(renderer);
// }
