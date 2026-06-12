export module backend:rendercompiler;

export struct Vertex {
  float x, y, z;
};

export struct Face {
  Vertex v1, v2, v3;
};

export using Vertices = std::vector<Face>;

export class RenderCompiler {
public:

  void compile(const CommandBuffer&);
};
