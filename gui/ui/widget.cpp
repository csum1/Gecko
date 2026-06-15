module;
#include <memory>
module ui;
import std;

void Widget::update() {
  std::println("update widget");
}

Size Widget::measure() {
  return Size{bounds_.width, bounds_.height};
}

void Widget::arrange(const Rect& bounds) {
  bounds_ = bounds;
}

void Widget::attach(std::unique_ptr<Widget>&& wdg) {
  child_ = std::move(wdg);
}

void Widget::draw(DrawContext& ctx) const {
  child_->draw(ctx);
}

