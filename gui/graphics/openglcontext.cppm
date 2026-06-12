module;

export module graphics:openglcontext;

export class OpenGLContext : public GraphicsContext {
  public:
    GraphicsContext& backend() override;

}
