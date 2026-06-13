module;
export module ui:button;
import std;
import :widget;
import :label;
import backend;

export struct ButtonStyle {
  Color background;
  Color hover;
  Color pressed;
  Color border;
  float radius;
};

export class Button final : public Widget {
public:
  using callback = std::function<void(Widget&)>;

  Button() = default;
  Button(std::string, callback = {});

  Button(const Button& other);
  Button(Button&&);

  Button& operator=(const Button&);
  Button& operator=(Button&&);

  void draw(DrawContext& ctx) const override;
  void onclick(callback);
  void click();

private:
  callback onClick_;
  ButtonStyle style_;
};

