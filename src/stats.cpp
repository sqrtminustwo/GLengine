#include <stats.h>
#include <GLFW/glfw3.h>

Stats::Stats() : screen(ftxui::ScreenInteractive::Fullscreen()) {
    renderer_text_fps = canvasWithVar(last_frames);
    renderer_text_avg_fps = canvasWithVar(avg_fps);
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

    menu_tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);

    container = ftxui::ResizableSplitLeft(tab_with_mouse, menu_tab_toggle, &right_size);

    // Main component/thread with rendering
    // https://github.com/ArthurSonzogni/FTXUI/blob/main/examples/component/canvas_animated.cpp
    component_renderer = Renderer(container, [this] { return container->Render() | ftxui::border; });
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
        avg_fps = getAvgFps();
        frames = 0;
        last_time = current_time;
    }
}
