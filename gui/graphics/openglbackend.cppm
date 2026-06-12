module;

export module graphics:openl;

import :graphicsbackend;

export class OpenGLBackend : public GraphicsBackend {
  public:
     void begin_frame() override;
     void end_frame() override;

}
