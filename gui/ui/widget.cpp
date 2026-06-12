module;

#include <print>

module ui;

void Widget::add(Widget&& wdg) {
  children_.push_back(std::unique_ptr<Widget>(wdg));
}

void Widget::draw(DrawContext& ctx) const {
  for (auto& child : children_) {
    child->draw(ctx);
  }
}

void Widget::update() {
  std::println("update widget");
  for(auto& child : children_) {
    child.update();
  }
}
