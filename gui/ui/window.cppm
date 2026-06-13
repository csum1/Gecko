module;

#include <string>

export module ui:window;

import :widget;
import backend;

export class Window {
  public:
    Window() = delete;
    Window(std::string&& title);    

    Window(const Window&) = delete;
    Window(Window&&) = default;

    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = default;

    virtual ~Window() = default;

    void update();
  private:
    Widget root_;
    std::string title_;
    CommandBuffer cmd_buffer_;
    DrawContext draw_ctx_;
    Renderer renderer_;
};
