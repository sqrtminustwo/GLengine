#ifndef STATS_H
#define STATS_H

#include "plot.h"
#include <terminal_screen.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

class Stats {
  public:
    Stats();

    void start();
    void updateFps();

    double getAvgFps() const { return ((double)total) / ((double)count); }

  private:
    std::vector<int> fps_history;
    int frames_counter;
    int last_frames;
    int total;
    int count;
    float last_time;
    float avg_fps;

    int selected_tab = 0;
    int size = 50;
    bool running = true;

    std::unique_ptr<TerminalScreen> terminal_screen;
    std::unique_ptr<Plot> plot;
    ftxui::Component renderer_text_fps;
    ftxui::Component renderer_text_avg_fps;
    std::vector<std::string> tab_titles;
    ftxui::Component tab;
    ftxui::Component menu_tab_toggle;
    ftxui::Component container;

    template <typename T>
    ftxui::Component canvasWithVar(T &var) {
        return ftxui::Renderer([this, &var] {
            auto c = ftxui::Canvas(30, 10);
            c.DrawText(0, 0, std::to_string(var));
            return canvas(std::move(c));
        });
    }
};

#endif
