export module backend:render;

import :drawcommands;

export class Renderer {
public:
  // virtual void submit(const DrawRectCommand&) = 0;
  // virtual void submit(const DrawTextCommand&) = 0;
  void render(const RenderQueue& queue) const;
private:
  void submit() const;

};
