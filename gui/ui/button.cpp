module;

#include <print>
#include <functional>
#include <string>
module ui;

Button::Button(std::string text, callback cb) :
  onClick_(std::move(cb)) 
{
  add(Label(std::move(text)));
  std::println("[Button] constructor std::string, callback");
}

Button::Button(const Button& other) :
  onClick_(other.onClick_)
{
  std::println("[Button] copy constructed");
}

Button::Button(Button&& other) :
  onClick_(std::move(other.onClick_))
{
  std::println("[Button] move constructed");
}

Button& Button::operator=(const Button& other) {
  onClick_ = other.onClick_;
  std::println("[Button] copy assigned");
  return *this;
}

Button& Button::operator=(Button&& other) {
  onClick_ = std::move(other.onClick_);
  std::println("[Button] move assigned");
  return *this;
}

void Button::onclick(callback cb) {
  onClick_ = std::move(cb);
}

void Button::click() {
  if (onClick_) {
    onClick_(*this);
  }
}

void Button::draw(DrawContext& ctx) const {
  ctx.draw_rect(bounds_, style_.background);
  Widget::draw(ctx);
}
