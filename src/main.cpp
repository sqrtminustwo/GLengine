#include <window.h>
#include <camera.h>
#include <cube.h>
#include <input.h>
#include <shader.h>
#include <stats.h>
#include <plot.h>

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

// #include <cmath> // for sin, cos
// #include <ctime>
// #include <ftxui/dom/elements.hpp>  // for canvas, Element, separator, hbox, operator|, border
// #include <ftxui/screen/screen.hpp> // for Pixel
// #include <iostream>
// #include <string>  // for string, basic_string
// #include <utility> // for move
// #include <vector>  // for vector, __alloc_traits<>::value_type
//
// #include "ftxui/component/component.hpp"          // for Renderer, CatchEvent, Horizontal, Menu, Tab
// #include "ftxui/component/component_base.hpp"     // for ComponentBase
// #include "ftxui/component/event.hpp"              // for Event
// #include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
// #include "ftxui/dom/canvas.hpp"                   // for Canvas
// #include <random>
//
// int genRandom(int lower, int upper) {
//     static std::random_device rd;  // obtain a random number from hardware
//     static std::mt19937 gen(rd()); // seed the generator
//     std::uniform_int_distribution<> distr(lower, upper);
//     return distr(gen);
// }
// int normalizeFps(int fps, int max) { return ((float)fps / (float)max) * 100; }
//
// int main() {
//     using namespace ftxui;
//
//     int max_fps = 240;
//     int max_points_in_one_graph = 20;
//     int step = 100 / max_points_in_one_graph;
//     std::vector<int> fps_history;
//
//     auto renderer_plot_1 = Renderer([&] {
//         auto c = Canvas(100, 100);
//
//         int size = fps_history.size();
//         int pos = size > max_points_in_one_graph ? size - max_points_in_one_graph : 0;
//
//         std::vector<int>::const_iterator first = fps_history.begin() + pos;
//         std::vector<int>::const_iterator last = fps_history.begin() + size;
//         std::vector<int> ys(first, last);
//
//         int coef = 1;
//         int x;
//         for (pos = 1; pos < ys.size(); pos++) {
//             x = coef * step;
//             coef++;
//             c.DrawText(0, 0, " " + std::to_string(x) + " " + std::to_string(pos) + " " + std::to_string(size));
//             c.DrawPointLine(x - step, normalizeFps(ys.at(pos - 1), max_fps), x, normalizeFps(ys.at(pos), max_fps));
//         }
//
//         auto y_axis_fps = vbox({text("240 "), filler(), text("120 "), filler(), text("60 "), filler(), text("0")});
//
//         return hbox(y_axis_fps, canvas(std::move(c)));
//     });
//
//     int selected_tab = 0;
//
//     auto tab = Container::Tab({renderer_plot_1}, &selected_tab);
//
//     std::vector<std::string> tab_titles = {"plot_1 simple"};
//     auto tab_toggle = Menu(&tab_titles, &selected_tab);
//
//     auto component = Container::Horizontal({
//         tab,
//         tab_toggle,
//     });
//
//     // Add some separator to decorate the whole component:
//     auto component_renderer = Renderer(component, [&] {
//         return hbox({
//                    tab->Render(),
//                    separator(),
//                    tab_toggle->Render(),
//                }) |
//                border;
//     });
//
//     auto screen = ScreenInteractive::FitComponent();
//     bool running = true;
//
//     std::thread screen_redraw{[&]() {
//         while (running) {
//             screen.PostEvent(ftxui::Event::Custom);
//             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         }
//     }};
//
//     std::thread screen_thread([&] { screen.Loop(component_renderer); });
//
//     int fps;
//     while (true) {
//         fps = genRandom(0, 180);
//         fps_history.push_back(fps);
//         // std::cout << normalizeFps(fps, max_fps) << "\n";
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//     }
//
//     running = false;
//     screen_redraw.join();
//     screen_thread.join();
//
//     return 0;
// }
