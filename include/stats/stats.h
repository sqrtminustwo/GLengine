#ifndef STATS_H
#define STATS_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

class Stats {
  public:
    Stats();
    ~Stats();

    void start() const;
    void updateFps();

    int getAvgFps() const { return total / count; }

  private:
    std::vector<int> fps_history;
    int total{};
    int count{};

    int frames_counter{};
    int last_frames{};
    float last_time{};
    int avg_fps{};

    int selected_tab = 0;
    int size = 50;
    bool running = true;

    struct HeaderHolder;
    std::unique_ptr<HeaderHolder> header_holder;

    ftxui::Component renderer_text_fps;
    ftxui::Component renderer_text_avg_fps;
    std::vector<std::string> tab_titles;
    ftxui::Component tab;
    ftxui::Component menu_tab_toggle;
    ftxui::Component container;

    template <typename T>
    ftxui::Component canvasWithVar(T &var) const {
        return ftxui::Renderer([this, &var] {
            auto c = ftxui::Canvas(30, 10);
            c.DrawText(0, 0, std::to_string(var));
            return canvas(std::move(c));
        });
    }
};

#endif
