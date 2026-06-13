module;
module ui;
import std;

void Widget::update() {
  std::println("update widget");
  // for(auto& child : children_) {
  //   child.update();
  // }
}

Size Widget::measure() {
  return Size{bounds_.width, bounds_.height};
}

void Widget::arrange(const Rect& bounds) {
  bounds_ = bounds;
}

void Widget::add(Widget&& wdg) {
  // children_.push_back(std::unique_ptr<Widget>(wdg));
}

void Widget::draw(DrawContext& ctx) const {
  for (auto& child : children_) {
    child->draw(ctx);
  }
}

