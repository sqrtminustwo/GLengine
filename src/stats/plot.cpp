#include <plot.h>
#include <terminal_screen.h>
#include <ctime>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/canvas.hpp"

using namespace ftxui;

struct Plot::TerminalScreenHolder {
    std::unique_ptr<TerminalScreen> terminal_screen;
};

Plot::Plot(
    std::vector<int> &points, int max_y, ftxui::Color color, int y_split, int max_points_in_graph, int update_time
)
    : points(points), max_y(max_y), color(color), y_split(y_split), max_points_in_graph(max_points_in_graph),
      step(getStep()), update_time(update_time) {
    main_component = Renderer([this] {
        auto c = Canvas(100, 100);

        int size = this->points.size();
        int pos = size > this->max_points_in_graph ? size - this->max_points_in_graph : 0;

        int coef = 1;
        int x;
        for (pos += 1; pos < size; pos++) {
            x = coef * step;
            coef++;
            auto p1 = normalizePoint(this->points.at(pos - 1));
            auto p2 = normalizePoint(this->points.at(pos));
            // c.DrawText(1, 0, " " + std::to_string(p1) + " " + std::to_string(p2));
            c.DrawPointLine(x - step, p1, x, p2, this->color);
        }

        std::vector<Element> vec{};

        std::string e;
        for (int split = this->max_y; split > 0; split = std::max(split - this->y_split, 0)) {
            std::string e = std::to_string(split);
            vec.push_back(text(e));
            vec.push_back(filler());
        }
        if (vec.size() > 0) vec.pop_back(); // No filler needed after last element

        auto y_axis_fps = vbox(vec);

        return hbox(y_axis_fps, canvas(std::move(c))) | border;
    });
}

Plot::~Plot() = default;

void Plot::startPlotting() {
    checkMoved();
    terminal_screen_holder = std::make_unique<TerminalScreenHolder>();
    terminal_screen_holder->terminal_screen =
        std::unique_ptr<TerminalScreen>(new TerminalScreen(main_component, update_time));
    terminal_screen_holder->terminal_screen->start();
    moved = true;
}

ftxui::Component Plot::getPlot() {
    checkMoved();
    return main_component;
}
