import std;
import ui;

template<typename T>
void f(T&& param) {
  std::println("{}", param);
}

template void f(int&);

int cpp17(){
  [[maybe_unused]]
  std::variant<int, float> v{12};
  std::optional<std::string> test {};
  if (test) {
    std::printf("is some %s\n", test.value().data());
  }
  std::printf("is %s\n", test.value_or("None").data());
  return 0;
}

void cpp20() {
  std::print("test\n");
  std::println("test");
}

// void ui() {
//   std::vector<std::unique_ptr<Widget>> layer; 
//   layer.emplace_back(std::make_unique<Button>("test"));
//   layer.emplace_back(std::make_unique<Button>("u"));
//   layer.emplace_back(std::make_unique<Button>());
//
//   auto pbtn1 = std::make_unique<Button>("clickme");
//   pbtn1->onclick([](Widget& wdg){ std::println("clicked button"); });
//
//   // release() return T* and releases the ownership
//   auto btn1 = std::move(pbtn1.release());
//   btn1->draw();
//   delete btn1;
//   auto btn2 = Button("test", [](Widget& wdg){
//     std::println("without uniqueptr");
//   });
//   std::println("");
//
//   // std::make_unique placed the object on the heap!
//   // - is exception safe, cleaner as new, more efficient
//   auto pbtn2 = std::make_unique<Button>("test", [](Widget& wdg){
//     std::println("without uniqueptr");
//   });
//   auto pbtn3 = std::move(pbtn2);
//   // auto mtbt3 = tbt2; // does not compile: std::move(...) needed
//
//   auto pbtn4 = std::move(pbtn3);
//
//   for(const auto& w : layer) {
//     w->draw();
//   }
//   btn2.click();
//
//   f("test this printed");
//   Button btn{};
//   btn.draw();
// }

void cpp11() {

  // smart pointers:
  // cpp11_streams();



}

// void testcopy(std::unique_ptr<Button> btn) {
//   std::println("in testcopy to try out new button");
//   btn->click();
// }

int main(){
  // cpp11();
  // ui();
  std::println("This runs with import std;");
  App app("my App");
  app.run();
}

/*
 * c++11 
 * 
 *
 * c++14
 *
 *
 * c++17
 * std::variant
 * std::optional
 *
 *
 * c++20
 *
 *
 * c++23
 */
