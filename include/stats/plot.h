#ifndef PLOT_H
#define PLOT_H

#include <terminal_screen.h>
#include <ftxui/component/component_base.hpp>
#include <vector>

class Plot {
  public:
    Plot(int max_y, int max_points_in_graph);

    void startPlotting();

    void setMaxY(int max_y) { this->max_y = max_y; }
    void setMaxPointInGraph(int max_points_in_graph) {
        this->max_points_in_graph = max_points_in_graph;
        step = getStep();
    };

    ftxui::Component getGraph();

  private:
    int normalizePoint(int point) { return ((float)point / (float)max_y) * 100; }
    int getStep() { return 100 / max_points_in_graph; }
    int genRandom(int lower, int upper);

    int max_y;
    int max_points_in_graph;
    int step;
    std::vector<int> &points;
};

#endif
