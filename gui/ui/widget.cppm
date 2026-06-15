module;
export module ui:widget;
import std;
import common;
import backend;

export class Widget {
public:
  Widget() = default;

  Widget(const Widget &) = delete;
  Widget(Widget &&) = default;

  Widget &operator=(const Widget &) = delete;
  Widget &operator=(Widget &&) = default;

  virtual ~Widget() = default;

  virtual void update();
  virtual Size measure();
  virtual void arrange(const Rect&);
  virtual void draw(DrawContext&) const;

  void attach(std::unique_ptr<Widget>&&);

protected:
  std::unique_ptr<Widget> child_;
  Rect bounds_;
private:
};
