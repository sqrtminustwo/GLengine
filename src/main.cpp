#include <window.h>
#include <camera.h>
#include <cube.h>
#include <input.h>
#include <shader.h>
#include <stats.h>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"

int main() {

    Window window(1280, 1000, std::tuple(0, 0, 0, 0.7));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shape_shader(
        "../../resources/shaders/shape/vertex_shader.glsl",
        "../../resources/shaders/shape/fragment_shader.glsl"
    );

    Shader text_shader(
        "../../resources/shaders/text/vertex_shader.glsl",
        "../../resources/shaders/text/fragment_shader.glsl"
    );

    std::vector<Cube *> cubes;

    Cube cube1{};
    cubes.push_back(&cube1);

    Cube cube2{cube1};
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, glm::vec3(-2.0f, -2.0f, 1.0f));
    cube2.setTranslationMatrix(translate);
    cubes.push_back(&cube2);

    char background[] = "../../resources/textures/yellow.png";
    char frame[] = "../../resources/textures/frame4.png";
    shape_shader.loadTexture(background);
    shape_shader.loadTexture(frame);
    shape_shader.setProjectionMatrix(cube1.getProjectionMatrix());

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shape_shader.setScaleMatrix(scaleDown);

    // TODO: move to stats class
    // TODO: function for both lambdas (reduce code duplication)
    Stats stats{};
    int fps = 0;
    double avg_fps = 0;
    auto renderer_text_fps = ftxui::Renderer([&] {
        auto c = ftxui::Canvas(30, 10);
        c.DrawText(0, 0, std::to_string(fps));
        return canvas(std::move(c));
    });
    auto renderer_text_avg_fps = ftxui::Renderer([&] {
        auto c = ftxui::Canvas(30, 10);
        c.DrawText(0, 0, std::to_string(avg_fps));
        return canvas(std::move(c));
    });

    // Selected tab
    int selected_tab = 0;
    auto tab = ftxui::Container::Tab({renderer_text_fps, renderer_text_avg_fps}, &selected_tab);

    // Mouse hovered on the container in terminal
    // Updates both renderer_text and selected_tab
    int mouse_x = 0;
    int mouse_y = 0;

    auto tab_with_mouse = CatchEvent(tab, [&](ftxui::Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 1) * 2;
            mouse_y = (e.mouse().y - 1) * 4;
        }
        return false;
    });

    std::vector<std::string> tab_titles = {"fps", "avg fps"};
    auto tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);

    auto component = ftxui::Container::Horizontal({
        tab_with_mouse,
        tab_toggle,
    });

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();

    // Side thread to constantly call redraw of main component (so updated even when not hovered)
    // https://github.com/ArthurSonzogni/FTXUI/wiki/Screen#force-redraw
    bool running = true;
    std::thread screen_redraw([&]() {
        while (running) {
            screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Prevent High CPU Usage.
        }
    });

    // Main component/thread with rendering
    // https://github.com/ArthurSonzogni/FTXUI/blob/main/examples/component/canvas_animated.cpp
    auto component_renderer = Renderer(component, [&] {
        return ftxui::hbox({
                   tab_with_mouse->Render(),
                   ftxui::separator(),
                   tab_toggle->Render(),
               }) |
               ftxui::border;
    });
    std::thread screen_thread{[&] { screen.Loop(component_renderer); }};

    while (!glfwWindowShouldClose(window.getWindow())) {
        stats.updateFps();
        fps = stats.getFps();
        avg_fps = stats.getAvgFps();

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

    // Screen should be exited before closing threads (idk why)
    running = false;
    screen.Exit();
    screen_redraw.join();
    screen_thread.join();

    for (Cube *cube : cubes) cube->destruct();
    glfwTerminate();
    return 0;
}
