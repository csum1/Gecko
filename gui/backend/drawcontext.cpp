module;
module backend;
import :drawcommands;
import common;

DrawContext::DrawContext(CommandBuffer& cmd_buffer) :
  cmd_buffer_(cmd_buffer) {
  
}

void DrawContext::draw_rect(Rect rect, Color color) {
  auto* cmd = cmd_buffer_.create<DrawRectCommand>(CommandType::DrawRect);
  cmd->rect = rect;
  cmd->color = color;
}

void DrawContext::draw_rounded_rect(Rect rect, float radius, Color color) {
  auto* cmd = cmd_buffer_.create<DrawRoundedRectCommand>(CommandType::DrawRoundedRect);
  cmd->rect = rect;
  cmd->color = color;
}
