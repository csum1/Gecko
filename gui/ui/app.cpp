module;
#include <GLFW/glfw3.h>
module ui;
import std;
import :window;

App::App(std::string&& title) : title_(title) {

}

void App::run() {
  auto result = create_window();
  if (!result) {
    std::println("{}", result.error());
    return;
  }
  auto& window = result.value();

  while(!glfwWindowShouldClose(window)) {
    update();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void App::update() {
  for(auto& win : windows_) {
    win.update();
  }
}

std::expected<GLFWwindow*, std::string> App::create_window() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return std::unexpected("Could not initialize glfw library");
  }

  window = glfwCreateWindow(600, 400, title_.c_str(), NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return std::unexpected("Could not create glfw window");
  }

  glfwMakeContextCurrent(window);

  return window;
}

void App::add_window(Window&& window) {
  // windows_.push_back(window);
}

