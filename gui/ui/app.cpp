module;
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
module ui;
import std;
import :window;

App::App(std::string&& title) : 
  title_(title) {

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

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data) {
    std::cerr << "Validation layer: " << callback_data->pMessage << std::endl;
    return VK_FALSE;
}

// bool check_validation_layer_support() {
//   uint32_t layer_count;
//   vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
//   std::vector<VkLayerProperties> layers(layer_count);
//   vkEnumerateInstanceLayerProperties(&layer_count, layers.data());
//   for (const char* layer_name : validation_layers) {
//     bool found = false;
//     for (const auto& layerProps : layers) {
//       if (strcmp(layer_name, layerProps.layerName) == 0) {
//         found = true;
//         break;
//       }
//     }
//     if (!found) return false;
//   }
//   return true;
// }

std::expected<GLFWwindow*, std::string> App::create_window() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return std::unexpected("Could not initialize glfw library");
  }

  // disable OpenGL context creation
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(600, 400, title_.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    return std::unexpected("Could not create glfw window");
  }

  glfwMakeContextCurrent(window);

  // Vulkan setup
  if (glfwVulkanSupported() != GLFW_TRUE) {
    return std::unexpected("Vulkan not supported");
  }

  const char* layers[] = {
    "VK_LAYER_KHRONOS_validation"
  };

  // VkDebugUtilsMessengerCreateInfoEXT debug_ci{};
  // debug_ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  // debug_ci.messageSeverity =
  //     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
  //     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  // debug_ci.messageType =
  //     VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
  //     VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
  //     VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  // debug_ci.pfnUserCallback = debug_callback;

  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "GUI with Vulkan";
  app_info.applicationVersion = VK_MAKE_VERSION(1,0,0);
  app_info.pEngineName = "My Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1,0,0);
  app_info.apiVersion = VK_API_VERSION_1_3;

  uint32_t extension_count;
  const char** extensions = glfwGetRequiredInstanceExtensions(&extension_count);

  // std::vector<const char*> extensions(glfw_extensions, glfw_extensions + extension_count);

  VkInstanceCreateInfo instance_ci{};
  std::memset(&instance_ci, 0, sizeof(instance_ci));
  instance_ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_ci.pApplicationInfo = &app_info;
  instance_ci.enabledExtensionCount = extension_count;
  instance_ci.ppEnabledExtensionNames = extensions;
  instance_ci.enabledLayerCount = 0;
  // instance_ci.pNext = &debug_ci;

  // auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
  //   vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  // func(instance, &debugCreateInfo, nullptr, &debugMessenger);

  VkInstance instance = VK_NULL_HANDLE;
  if (vkCreateInstance(&instance_ci, nullptr, &instance) != VK_SUCCESS) {
    return std::unexpected("Could not create Vulkan instance");
  }

  VkSurfaceKHR surface = VK_NULL_HANDLE;
  if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
    return std::unexpected("Could not create window surface");
  }

  // if (glfwGetPhysicalDevicePresentationSupport(instance, physical_device, queue_family_index)) {
  //
  // }

  return window;
}

void App::add_window(Window&& window) {
  // windows_.push_back(window);
}

