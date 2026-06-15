module;
export module ui:layout;
import std;
import :widget;

export class Layout {
public:
  Layout() = default;
  Layout(const Layout&) = delete;
  Layout(Layout&&) = default;

  Layout& operator=(const Layout&) = delete;
  Layout& operator=(Layout&&) = default;

  virtual ~Layout() = default;

protected:
  std::vector<std::unique_ptr<Widget>> children_;
};
