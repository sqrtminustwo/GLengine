#ifndef PLOT_H
#define PLOT_H

#include <ftxui/screen/color.hpp>
#include <ftxui/component/component.hpp>
#include <vector>
#include <memory>

class Plot {
  public:
    Plot(
        const std::vector<int> &points, int max_y, ftxui::Color color = ftxui::Color::White, int y_split = 10,
        int max_points_in_graph = 10, int update_time = 500
    );
    ~Plot();

    void startPlotting();

    void setMaxY(const int max_y) { this->max_y = max_y; }
    void setMaxPointsInGraph(const int max_points_in_graph) {
        this->max_points_in_graph = max_points_in_graph;
        step = getStep();
    };
    void setYSplit(const int y_split) { this->y_split = y_split; }
    void setColor(const ftxui::Color color) { this->color = color; }

    ftxui::Component getPlot() const;

  private:
    inline int normalizePoint(const int point) const { return ((float)(max_y - point) / (float)max_y) * 100; }
    int getStep() const { return 100 / max_points_in_graph; }
    void checkMoved() const {
        if (moved) throw std::runtime_error("Was used for plotting, can't reuse!");
    }

    struct TerminalScreenHolder;
    std::unique_ptr<TerminalScreenHolder> terminal_screen_holder;

    ftxui::Component main_component;
    int max_y;
    ftxui::Color color;
    int y_split;
    int max_points_in_graph;
    int step;
    // In ms (value below 50ms will cause high cpu load)
    int update_time;
    bool moved = false;
    const std::vector<int> &points;
};

#endif
