#include <stats.h>
#include <GLFW/glfw3.h>
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"
#include <iostream>

Stats::Stats() : screen(ftxui::ScreenInteractive::Fullscreen()) {
    // TODO: function for both lambdas (reduce code duplication)
    renderer_text_fps = ftxui::Renderer([this] {
        auto c = ftxui::Canvas(30, 10);
        c.DrawText(0, 0, std::to_string(last_frames));
        return canvas(std::move(c));
    });
    renderer_text_avg_fps = ftxui::Renderer([this] {
        auto c = ftxui::Canvas(30, 10);
        c.DrawText(0, 0, std::to_string(avg_fps));
        return canvas(std::move(c));
    });

    // Selected tab
    tab = ftxui::Container::Tab({renderer_text_fps, renderer_text_avg_fps}, &selected_tab);

    // Mouse hovered on the container in terminal
    // Updates both renderer_text and selected_tab
    mouse_x = 0;
    mouse_y = 0;

    tab_with_mouse = CatchEvent(tab, [this](ftxui::Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 1) * 2;
            mouse_y = (e.mouse().y - 1) * 4;
        }
        return false;
    });

    tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);

    component = ftxui::Container::Horizontal({
        tab_with_mouse,
        tab_toggle,
    });

    // Main component/thread with rendering
    // https://github.com/ArthurSonzogni/FTXUI/blob/main/examples/component/canvas_animated.cpp
    component_renderer = Renderer(component, [this] {
        return ftxui::hbox({
                   tab_with_mouse->Render(),
                   ftxui::separator(),
                   tab_toggle->Render(),
               }) |
               ftxui::border;
    });
}

void Stats::start() {
    screen_redraw = std::thread{[this]() {
        while (running) {
            screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }};

    screen_thread = std::thread{[this]() { screen.Loop(component_renderer); }};
}

Stats::~Stats() {
    running = false;
    screen.Exit();
    screen_redraw.join();
    screen_thread.join();
}

void Stats::updateFps() {
    frames++;
    double current_time = glfwGetTime();
    if (current_time - last_time >= 1) {
        count++;
        total += frames;
        last_frames = frames;
        frames = 0;
        last_time = current_time;
    }
}
