module;
module ui;
import std;

Label::Label(std::string&& text) : text_(text) {

}
    
void Label::draw(DrawContext& ctx) const {
  
  std::print("{}", text_);
}
