module;
#include <cstdint>
#include "vulkan/vulkan.hpp"
#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
module ui;
import std;
import :window;

const char* AppError::what() const noexcept {
  return message_.c_str();
}

App::App(AppSetting&& setting) : 
  setting_(setting) {

}

void App::init() {
  if (!glfwInit()) {
    throw AppError("Could not initialize glfw library");
  }
}

void App::run() {
  init();
  auto* window = create_window();
  init_graphics(window);

  while(!glfwWindowShouldClose(window)) {
    update();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
}

void App::add_window([[maybe_unused]] Window&& window) {
  // windows_.push_back(window);
}

void App::update() {
  for(auto& win : windows_) {
    win.update();
  }
}


void App::cleanup() {

}


GLFWwindow* App::create_window() {
  GLFWwindow* window;

  // disable OpenGL context creation
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(600, 400, setting_.title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw AppError("Could not create glfw window");
  }

  glfwMakeContextCurrent(window);

  return window;
}

void App::init_graphics(GLFWwindow* window) {

  if (glfwVulkanSupported() != GLFW_TRUE) {
    throw AppError("Vulkan not supported");
  }
 
  // Required extensions
  // check if extensions are available
  uint32_t glfw_extension_count;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  std::vector required_extensions(glfw_extensions, glfw_extensions + glfw_extension_count);
  auto extension_properties = context_.enumerateInstanceExtensionProperties();

  if (setting_.verbose) {
    std::println("[VERBOSE] Extension Properties:");
    for (const auto& extension : extension_properties) {
      std::cout << extension.extensionName << "\n";
    }
  }

  auto unsupported_property_it = std::ranges::find_if(required_extensions,
    [&extension_properties](auto const &required_extension) {
      return std::ranges::none_of(extension_properties,
        [required_extension](auto const &extension_property) {
          return strcmp(extension_property.extensionName, required_extension) == 0;
        }
      );
    }
  );

  if (unsupported_property_it != required_extensions.end()) {
    throw AppError("Required GLFW extension not supported: {}", *unsupported_property_it);
  }

  // Validation layers
  std::vector<char const*> required_layers = {
    "VK_LAYER_KHRONOS_validation"
  };

  auto layer_properties = context_.enumerateInstanceLayerProperties();
  auto unsupported_layer_it = std::ranges::find_if(required_layers,
    [&layer_properties](auto const& required_layer) {
      return std::ranges::none_of(layer_properties, 
        [required_layer](auto const& layer_property) {
          return strcmp(layer_property.layerName, required_layer) == 0;
        }
      );
    }
  );

  if (unsupported_layer_it != required_layers.end()) {
    throw AppError("Required layer not supported: {}", *unsupported_layer_it);
  }

  // Vulkan instance setup
  constexpr vk::ApplicationInfo app_info {
    .pApplicationName = "GUI with Vulkan",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "My Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = vk::ApiVersion14
  };

  vk::InstanceCreateInfo instance_ci {
    .pApplicationInfo = &app_info,
      .enabledExtensionCount = glfw_extension_count,
      .ppEnabledExtensionNames = glfw_extensions
  };

  throw AppError("test");

  try {
    instance_ = vk::raii::Instance(context_, instance_ci);
    
  } catch (const vk::SystemError& err) {
    throw AppError("-Vulkan: {}", err.what());
  } catch (const std::exception& err) {
    throw AppError("{}", err.what());
  }

  // if (vkCreateInstance(&instance_ci, nullptr, &instance) != VK_SUCCESS) {
  //   return std::unexpected("Could not create Vulkan instance");
  // }
  //
  // VkSurfaceKHR surface = VK_NULL_HANDLE;
  // if (glfwCreateWindowSurface(instance_, window, nullptr, &surface) != VK_SUCCESS) {
  //   return std::unexpected("Could not create window surface");
  // }

  // if (glfwGetPhysicalDevicePresentationSupport(instance, physical_device, queue_family_index)) {
  //
  // }

  return; 
}
