module;

#include <string>

module ui;

Window::Window(std::string&& title) : title_(title){
  std::println("window {} created", title_);
}

void Window::update() {
  draw_ctx_.
  root_.draw(draw_ctx_);
}
