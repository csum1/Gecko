module;
module ui;
import std;

Window::Window(std::string&& title) : 
  title_(title),
  draw_ctx_(cmd_buffer_)
{
  std::println("window {} created", title_);
}

void Window::update() {
  // draw_ctx_.
  // root_.draw(draw_ctx_);
}
