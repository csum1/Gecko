module;
export module graphics:context;

export class GraphicsContext {
  public:
    virtual GraphicsBackend& backend() = 0;
}
