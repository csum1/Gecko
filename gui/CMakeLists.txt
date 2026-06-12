cmake_minimum_required(VERSION 4.1)

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
  PRIVATE
    backend/drawcontext.cpp
)

set_target_properties(gecko PROPERTIES 
  VERIFY_INTERFACE_HEADER_SETS ON
)

target_compile_features(gecko PRIVATE cxx_std_23)

target_compile_options(gecko PRIVATE 
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  # $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors -Werror>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors>
  # -stdlib=libc++
)
