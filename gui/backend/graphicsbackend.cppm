module;
export module graphics:backend;

/*
 * support for 
 * rectangles
 * rounded rectangles
 * borders
 * gradients
 * text
 * images
 * clipping
 * transforms
 * opacity
 *
 * CPU tesselation: generate vertices
 * GPU signed distance field shader: scalable, anti-aliased, arbitrary radius
 *
 * text: freetype = font -> glyph atlas -> texture
 * batching: not single draw calls use:
 *  all rectangles -> one buffer, all text -> one buffer
 *  renderer sorts commands
 *
 * clipping for scroll areas, lists, text boxes
 */

export class GraphicsBackend {
  public:
    virtual void begin_frame() = 0;
    virtual void end_frame() = 0;
    virtual void upload_vertices() = 0;
    virtual void bind_pipeline() = 0;
    virtual void draw(uint32_t offset, uint32_t count) = 0;

  private:

}
