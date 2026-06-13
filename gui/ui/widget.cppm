module;
export module ui:widget;
import std;
import common;
import backend;

export class Widget {
public:
  Widget() = default;

  Widget(const Widget &) = default;
  Widget(Widget &&) = default;

  Widget &operator=(const Widget &) = default;
  Widget &operator=(Widget &&) = default;

  virtual ~Widget() = default;

  virtual void update();
  virtual Size measure();
  virtual void arrange(const Rect&);
  virtual void draw(DrawContext&) const;

  void add(Widget&&);

protected:
  std::vector<std::unique_ptr<Widget>> children_;
  Rect bounds_;
private:
};
