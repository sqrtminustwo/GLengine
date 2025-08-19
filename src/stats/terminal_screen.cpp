#include <terminal_screen.h>

TerminalScreen::TerminalScreen(ftxui::Component main_component, int update_time)
    : screen(ftxui::ScreenInteractive::FitComponent()), main_component(std::move(main_component)),
      update_time(update_time) {}

void TerminalScreen::start() {
    running = true;

    screen_redraw = std::thread{[this]() {
        while (running) {
            screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
        }
    }};

    screen_thread = std::thread{[this]() { screen.Loop(main_component); }};
}

TerminalScreen::~TerminalScreen() {
    if (!running) return;
    running = false;
    screen.Exit();
    screen_redraw.join();
    screen_thread.join();
}
