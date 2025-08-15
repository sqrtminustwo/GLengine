#ifndef STATS_H
#define STATS_H

#include <ftxui/component/screen_interactive.hpp>

class Stats {
  public:
    Stats();
    ~Stats();

    void start();
    void updateFps();

    double getAvgFps() const { return ((double)total) / ((double)count); }
    int getFps() const { return last_frames; }

  private:
    int fps = 0;
    int avg_fps = 0;
    int selected_tab = 0;
    int mouse_x = 0;
    int mouse_y = 0;
    bool running = true;
    int count = 0;
    double last_time;
    int frames = 0;
    int last_frames = 0;
    int total = 0;

    ftxui::Component renderer_text_fps;
    ftxui::Component renderer_text_avg_fps;
    std::vector<std::string> tab_titles = {"fps", "avg fps"};
    ftxui::Component tab;
    ftxui::Component tab_with_mouse;
    ftxui::Component tab_toggle;
    ftxui::Component component;
    ftxui::Component component_renderer;

    ftxui::ScreenInteractive screen;

    std::thread screen_redraw;
    std::thread screen_thread;
};

#endif
