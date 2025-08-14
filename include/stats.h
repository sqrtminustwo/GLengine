#ifndef STATS_H
#define STATS_H

#include <ftxui/component/screen_interactive.hpp>

class Stats {
  public:
    Stats();

    // void startStats();
    // void endStats();
    void updateFps();

    double getAvgFps() const { return ((double)total) / ((double)count); }
    int getFps() const { return last_frames; }

  private:
    // ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    // ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();
    // std::thread screen_thread;
    // bool running = true;
    double last_time;
    int frames = 0;
    int last_frames = 0;
    int total = 0;
    int count = 0;
};

#endif
