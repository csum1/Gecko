module;

#include <print>

module ui;

Label::Label(std::string&& text) : text_(text) {

}
    
void Label::draw() const {
  std::print("{}", text_);
}
