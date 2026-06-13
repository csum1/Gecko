module;

#include <string>

export module ui:label;

import :widget;
import backend;

export class Label : public Widget {
public:
  Label() = delete;
  Label(std::string&&);
  Label(const Label&) = default;
  Label(Label&&) = default;

  Label& operator=(const Label&) = default;
  Label& operator=(Label&&) = default;

  void draw(DrawContext&) const override;

private:
  std::string text_;
};
