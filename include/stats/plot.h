#ifndef PLOT_H
#define PLOT_H

#include <terminal_screen.h>
#include <ftxui/screen/color.hpp>
#include <vector>
#include <memory>

class Plot {
  public:
    Plot(
        std::vector<int> &points, int max_y, ftxui::Color color = ftxui::Color::White, int y_split = 10,
        int max_points_in_graph = 10, int update_time = 500
    );

    void startPlotting();

    void setMaxY(int max_y) { this->max_y = max_y; }
    void setMaxPointsInGraph(int max_points_in_graph) {
        this->max_points_in_graph = max_points_in_graph;
        step = getStep();
    };
    void setYSplit(int y_split) { this->y_split = y_split; }
    void setColor(ftxui::Color color) { this->color = color; }

    ftxui::Component getPlot();

  private:
    int normalizePoint(int point) { return ((float)(max_y - point) / (float)max_y) * 100; }
    int getStep() { return 100 / max_points_in_graph; }

    std::unique_ptr<TerminalScreen> terminal_screen;
    ftxui::Component main_component;
    int max_y;
    ftxui::Color color;
    int y_split;
    int max_points_in_graph;
    int step;
    // In ms (value below 50ms will cause high cpu load)
    int update_time;
    bool moved = false;
    std::vector<int> &points;
};

#endif
