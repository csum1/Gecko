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
  std::println("initialize application...");
  init();

  std::println("create window...");
  auto* window = create_window();

  std::println("initialize graphics...");
  init_graphics(window);

  std::println("enter runloop...");
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

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
    vk::DebugUtilsMessageTypeFlagsEXT type,
    const vk::DebugUtilsMessengerCallbackDataEXT *p_callback_data,
    [[maybe_unused]] void *p_user_data) {
  switch(severity) {
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
      std::cerr << "[VERBOSE] ";
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
      std::cerr << "[INFO] ";
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
      std::cerr << "[WARNING] ";
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
      std::cerr << "[ERROR] ";
      break;
  }

  std::cerr << "validation layer:" 
    << " type: " << to_string(type) 
    << " msg: " << p_callback_data->pMessage << std::endl;
  return vk::False;
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
  // enable validation layer
  required_extensions.push_back(vk::EXTDebugUtilsExtensionName);
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
    .enabledLayerCount = static_cast<uint32_t>(required_layers.size()),
    .ppEnabledLayerNames = required_layers.data(),
    .enabledExtensionCount = static_cast<uint32_t>(required_extensions.size()),
    .ppEnabledExtensionNames = required_extensions.data()
  };

  instance_ = vk::raii::Instance(context_, instance_ci);
  vk::raii::DebugUtilsMessengerEXT debug_messenger = nullptr;

  // setup debug messenger
  vk::DebugUtilsMessageSeverityFlagsEXT severity_flags(
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);

  vk::DebugUtilsMessageTypeFlagsEXT message_type_flags(
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
      vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
      vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

  vk::DebugUtilsMessengerCreateInfoEXT debug_utils_messenger_ci_ext{
    .messageSeverity = severity_flags,
    .messageType = message_type_flags,
    .pfnUserCallback = &debug_callback
  };

  debug_messenger = instance_.createDebugUtilsMessengerEXT(debug_utils_messenger_ci_ext);

  // device
  vk::raii::PhysicalDevice physical_device = nullptr;
  auto physical_devices = instance_.enumeratePhysicalDevices();
  if (physical_devices.empty()) {
    throw AppError("no GPU with vulkan support");
  }
  std::vector<vk::raii::PhysicalDevice> usable_devices;

  std::cout << "=== "<< physical_devices.size() << " Devices found ===\n";
  for (const auto& physical_device : physical_devices) {
    auto device_properties = physical_device.getProperties();
    auto device_features = physical_device.getFeatures();

    const char* device_type;

    switch (device_properties.deviceType) {
      case vk::PhysicalDeviceType::eDiscreteGpu:
        device_type = "DiscreteGPU";
        break;
      case vk::PhysicalDeviceType::eCpu:
        device_type = "CPU";
        break;
      case vk::PhysicalDeviceType::eIntegratedGpu:
        device_type = "IntegratedGpu";
        break;
      case vk::PhysicalDeviceType::eVirtualGpu:
        device_type = "VirtualGpu";
        break;
      case vk::PhysicalDeviceType::eOther:
        device_type = "Other";
        break;
    }

    std::cout
      << "== Device\n"
      << "  name: " << device_properties.deviceName << "\n"
      << "  device type: " << device_type
      << "  vendor ID: " << device_properties.vendorID << "\n"
      << "  device ID: " << device_properties.deviceID << "\n"
      << "  api version: " << device_properties.apiVersion << "\n"
      << "  sparseProperties: " << device_properties.sparseProperties << "\n"
      << "  driver version: " << device_properties.driverVersion << "\n"
      << "  geometry shader: " << device_features.geometryShader << "\n"
      << "\n";


    auto queue_families = physical_device.getQueueFamilyProperties();
    bool supports_graphics = std::ranges::any_of(queue_families, [](auto const &qfp) {
        return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });


    // check device extesions
    std::vector<const char*> required_device_extensions = {
      vk::KHRSwapchainExtensionName
    };
    auto available_device_extensions = physical_device.enumerateDeviceExtensionProperties();
    bool supports_required_extensions = std::ranges::all_of(required_device_extensions,
      [&available_device_extensions](auto const & required_device_extension ) {
        return std::ranges::any_of(available_device_extensions,
          [required_device_extension](auto const & available_device_extension) {
            return strcmp(
                available_device_extension.extensionName, required_device_extension) == 0;
          }
        );
      }
    );

    auto features = physical_device.template getFeatures2<vk::PhysicalDeviceFeatures2,
         vk::PhysicalDeviceVulkan11Features,
         vk::PhysicalDeviceVulkan13Features,
         vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();
    bool supports_required_features =
      features.template get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
      features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
      features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

    if (
      device_properties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu ||
      !device_features.geometryShader ||
      device_properties.apiVersion < vk::ApiVersion13 ||
      !supports_graphics ||
      !supports_required_extensions ||
      !supports_required_features
      ) {
      continue;
    }

    usable_devices.push_back(physical_device);
  }

  if (usable_devices.empty()) {
    throw AppError("no suitable device found");
  }

  vk::raii::Device device = nullptr;

  // } catch (const vk::SystemError& err) {
  //   throw AppError("-Vulkan: {}", err.what());
  // } catch (const std::exception& err) {
  //   throw AppError("{}", err.what());
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
