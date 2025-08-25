#include <GLFW/glfw3.h>
#include <stats.h>
#include <plot.h>
#include <terminal_screen.h>

struct Stats::HeaderHolder {
    std::unique_ptr<Plot> plot;
    std::unique_ptr<TerminalScreen> terminal_screen;
};

Stats::Stats() {
    header_holder = std::make_unique<HeaderHolder>();
    header_holder->plot = std::unique_ptr<Plot>(new Plot(fps_history, 240, ftxui::Color::White, 10, 20, 1000));
    renderer_text_fps = canvasWithVar(last_frames);
    renderer_text_avg_fps = canvasWithVar(avg_fps);

    tab = ftxui::Container::Tab(
        {header_holder->plot->getPlot(), renderer_text_fps, renderer_text_avg_fps},
        &selected_tab
    );
    tab_titles = {"fps graph", "fps", "avg fps"};
    menu_tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);

    container = ftxui::ResizableSplitLeft(tab, menu_tab_toggle, &size);

    // Main component/thread with rendering
    // https://github.com/ArthurSonzogni/FTXUI/blob/main/examples/component/canvas_animated.cpp
    ftxui::Component main_component = Renderer(container, [this] { return container->Render() | ftxui::border; });
    header_holder->terminal_screen = std::unique_ptr<TerminalScreen>(new TerminalScreen(main_component, 1000));

    last_time = glfwGetTime();
}
Stats::~Stats() = default;

void Stats::start() const { header_holder->terminal_screen.get()->start(); }

void Stats::updateFps() {
    frames_counter++;
    float current_time = glfwGetTime();
    if (current_time - last_time >= 1) {
        count++;
        total += frames_counter;
        last_frames = frames_counter;
        fps_history.push_back(last_frames);
        avg_fps = getAvgFps();

        frames_counter = 0;
        last_time = current_time;
    }
}
