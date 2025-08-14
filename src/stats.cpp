#include <stats.h>
#include <GLFW/glfw3.h>
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"
#include <iostream>

Stats::Stats() {
    last_time = glfwGetTime();
    // auto renderer_text = ftxui::Renderer([&] {
    //     auto c = ftxui::Canvas(30, 10);
    //     c.DrawText(0, 0, std::to_string(last_frames));
    //     return canvas(std::move(c));
    // });
    //
    // int selected_tab = 1;
    // auto tab = ftxui::Container::Tab({renderer_text}, &selected_tab);
    //
    // int mouse_x = 0;
    // int mouse_y = 0;
    //
    // auto tab_with_mouse = CatchEvent(tab, [&](ftxui::Event e) {
    //     if (e.is_mouse()) {
    //         mouse_x = (e.mouse().x - 1) * 2;
    //         mouse_y = (e.mouse().y - 1) * 4;
    //     }
    //     return false;
    // });
    //
    // std::vector<std::string> tab_titles = {"fps"};
    // auto tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);
    //
    // auto component = ftxui::Container::Horizontal({
    //     tab_with_mouse,
    //     tab_toggle,
    // });
    //
    // auto component_renderer = Renderer(component, [&] {
    //     return ftxui::hbox({
    //                tab_with_mouse->Render(),
    //                ftxui::separator(),
    //                tab_toggle->Render(),
    //            }) |
    //            ftxui::border;
    // });
    //
    // ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();
    // std::thread screen_thread{[&] { screen.Loop(component_renderer); }};

    // auto screen = ftxui::ScreenInteractive::Fullscreen();
    //
    // auto text_renderer = ftxui::Renderer([this] {
    //     auto c = ftxui::Canvas(30, 10);
    //     c.DrawText(0, 0, std::to_string(last_frames));
    //     return canvas(std::move(c));
    // });
    //
    // std::thread screenRedraw([&, this]() {
    //     while (running) screen.Loop(text_renderer);
    // });
}

// void Stats::endStats() { running = false; }

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
