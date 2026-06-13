module;
export module backend:drawcontext;
import std;
import :drawcommands;
import common;

struct DrawState {
  Rect clip;
  // Mat3 transform;
  float opacity;
};

export class DrawContext final {
public:
  DrawContext(CommandBuffer& queue);
  DrawContext() = delete;
  
  DrawContext(const DrawContext&) = delete;
  DrawContext(DrawContext&&) = default;

  DrawContext& operator=(const DrawContext&) = delete;
  DrawContext& operator=(DrawContext&&) = default;

  void draw_rect(Rect rect, Color color);
  void draw_rounded_rect(Rect rect, float radius, Color color);
  // void draw_text();
  // void draw_image();
private:
  CommandBuffer& cmd_buffer_;
  std::stack<DrawState> state_;
};

