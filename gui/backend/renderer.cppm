export module backend:renderer;
import :drawcommands;

export class Renderer {
public:
  Renderer() = default;

  Renderer(const Renderer&) = delete;
  Renderer(Renderer&&) = default;

  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) = default;

  virtual ~Renderer() = default;

  // virtual void submit(const DrawRectCommand&) = 0;
  // virtual void submit(const DrawTextCommand&) = 0;
  void render(const CommandBuffer& cmd_buffer) const;
private:
  void submit() const;

};
