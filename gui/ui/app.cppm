module;

#include <string>
#include <vector>

export module ui:app;

import :widget;
import :window;

export class App final {
  public:
    App() = delete;
    App(std::string&& title);

    App(const App&) = delete;
    App(App&&) = default;

    App& operator=(App&&) = default;
    App& operator=(const App&) = delete;

    void run();
    void add_window(Window&& window);
  private:
    void update();
    std::expected<GLFWwindow*, std::string> create_window();
  protected:
    std::vector<Window> windows_;
    // LayoutEngine layout_engine_;
    std::string title_;
    bool running_;
};
