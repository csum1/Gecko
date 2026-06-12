module;
#include <string>
#include <vector>
#include <cstdint>
export module backend:drawcommands;

import common;

/*
 * using variants might be better than polymorphism
 * + each element has same size
 * + locality => cache friendly
 * - unused memory
 */ 
// using DrawCommand = std::variant<
//   DrawRectCommand,
//   DrawRoundedRectCommand,
//   DrawTextCommand
// >;

/*
 * Raw Command buffer
 * + tight memory packing
 * + very cache friendly
 * + avoid largest-type padding
 * + reduce memory bandwidth/latency
 */

export struct CommandBuffer final {
  template <typename T>
  T* create(CommandType type) {
    size_t offset = data.size();
    data.resize(offset + sizeof(CommandHeader) + sizeof(T));
    auto* header = reinterpret_cast<CommandHeader*>(data.data() + offset);
    auto* payload = reinterpret_cast<T*>(header + 1);
    header->type = type;
    header->size = sizeof(CommandHeader) + sizeof(T);
    return payload;
  }

  // TODO: std::byte creates an alignment problem => fix it later and compare performance
  std::vector<std::byte> data;
};

export enum class CommandType : uint32_t{
  DrawRect, DrawRoundedRect, DrawCircle, DrawText
};

export struct CommandHeader {
  CommandType type;
  uint16_t size;
};
 
export struct DrawRectCommand {
  Rect rect;
  Color color;
};

export struct DrawRoundedRectCommand {
  Rect rect;
  float radius;
  Color color;
};

export struct DrawTextCommand {
  Rect rect;
  Color color;
  std::string text;
};

