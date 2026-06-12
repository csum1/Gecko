module;

#include <cstdint>

export module common:primitives;

export struct Vec2 {
  float x, y;
};

export struct Veci2 {
  int32_t x, y;
};

export struct Color {
  float r, g, b;
};

export struct Size {
  float width;
  float height;
};

export struct Rect {
  float x;
  float y;
  float width;
  float height;
};


