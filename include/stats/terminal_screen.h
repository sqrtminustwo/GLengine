#ifndef TERMINAL_SCREEN_H
#define TERMINAL_SCREEN_H

#include <ftxui/component/screen_interactive.hpp>
#include <thread>

class TerminalScreen {
  public:
    TerminalScreen(ftxui::Component main_component, int update_time);
    ~TerminalScreen();

    void start();

  private:
    ftxui::ScreenInteractive screen;
    ftxui::Component main_component;

    bool running;
    // In ms, below 50 will cause high cpu load
    int update_time;
    std::thread screen_redraw;
    std::thread screen_thread;
};

#endif
