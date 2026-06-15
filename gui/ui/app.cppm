module;
#include <exception>
#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
export module ui:app;
import std;
import :widget;
import :window;

export class AppError : public std::exception {
  static constexpr std::string_view prefix = "[APPERROR] ";
public:
  template <typename... Args>
  AppError(std::format_string<Args...> fmt_str, Args&&... args) :
    message_(std::format("{}{}", prefix, 
      std::format(fmt_str, std::forward<Args>(args)...)))
    // trace_(std::stacktrace::current())
  {}

  // const std::stacktrace& stack() const noexcept {
  //   return trace_;
  // }

  const char* what() const noexcept override; 
private:
  std::string message_;
  // std::stacktrace trace_;
};

export struct AppSetting {
  std::string title = "default";
  bool verbose = true;
};

export class App final {
public:
  App() = delete;
  App(AppSetting&& setting);

  App(const App&) = delete;
  App(App&&) = default;

  App& operator=(App&&) = default;
  App& operator=(const App&) = delete;

  void run();
  void add_window(Window&& window);
private:
  void init();
  void update();
  void cleanup();
  GLFWwindow* create_window();
  void init_graphics(GLFWwindow* window);
protected:
  std::vector<Window> windows_;
  // LayoutEngine layout_engine_;
  AppSetting setting_;
private:
  bool running_;
  vk::raii::Context context_;
  vk::raii::Instance instance_ = nullptr;
};
