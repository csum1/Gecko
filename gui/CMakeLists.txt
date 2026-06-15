cmake_minimum_required(VERSION 4.1)

list(APPEND CMAKE_MESSAGE_CONTEXT gecko)

add_library(gecko)
target_sources(gecko
  # common module
  PUBLIC FILE_SET CXX_MODULES FILES
    common/common.cppm
    common/primitives.cppm
  PRIVATE

  # ui module
  PUBLIC FILE_SET CXX_MODULES FILES
  # FILE_SET cxx_modules TYPE CXX_MODULES FILES
    ui/ui.cppm
    ui/widget.cppm
    ui/label.cppm
    ui/button.cppm
    ui/app.cppm
    ui/window.cppm
    ui/layout.cppm
    ui/hlayout.cppm
    ui/vlayout.cppm
  PRIVATE
    ui/label.cpp
    ui/button.cpp
    ui/app.cpp
    ui/widget.cpp
    ui/window.cpp

  # backend module
  PUBLIC FILE_SET CXX_MODULES FILES
    backend/backend.cppm
    backend/drawcontext.cppm
    backend/drawcommands.cppm
    backend/renderer.cppm
  PRIVATE
    backend/drawcontext.cpp
    backend/renderer.cpp
)

set_target_properties(gecko PROPERTIES 
  VERIFY_INTERFACE_HEADER_SETS ON
  CXX_MODULE_STD ON
)
target_compile_features(gecko PRIVATE cxx_std_23)
target_compile_options(gecko PRIVATE 
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  # $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors -Werror>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors>
  # -stdlib=libc++
)

# use vulkan with modules
add_library(VulkanCppModule)
add_library(Vulkan::cppm ALIAS VulkanCppModule)
target_compile_definitions(VulkanCppModule PUBLIC
  VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
  VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
)
target_include_directories(VulkanCppModule PRIVATE "${Vulkan_INCLUDE_DIR}")
target_link_libraries(VulkanCppModule PUBLIC Vulkan::Vulkan)
set_target_properties(VulkanCppModule PROPERTIES CXX_STANDARD 23)
target_sources(VulkanCppModule
  PUBLIC
  FILE_SET cxx_modules TYPE CXX_MODULES
  BASE_DIRS "${Vulkan_INCLUDE_DIR}"
  FILES "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
)

target_link_libraries(gecko PRIVATE glfw Vulkan::cppm)
