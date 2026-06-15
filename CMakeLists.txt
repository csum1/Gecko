cmake_minimum_required(VERSION 4.1)
# must be set before project() call
# THIS IS CRITICAL - Enable experimental import std support
# cmake 4.1.0
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
# cmake 4.3.3
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

# CMAKE_CURRENT_SOURCE_DIR : directory of individual CMakeLists.txt
# PROJECT_SOURCE_DIR : directory of project
list(APPEND CMAKE_MESSAGE_CONTEXT Gui)
message(STATUS "Starting to create")

project(Gui 
  DESCRIPTION "A GUI for applications"
  LANGUAGES CXX
  VERSION 1.0 
)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "No in source builds.")
endif()

include(CTest)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(slang CONFIG REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# generates compile_commands.json
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_STD ON)

add_subdirectory(app)
add_subdirectory(gui)
add_subdirectory(test)

target_link_libraries(app PRIVATE gecko)

# get info of targets
# TARGETS, SOURCES, DIRECTORIES, TESTS, CACHE_ENTRIES
set(testvar "mytest")
include(CMakePrintHelpers)
cmake_print_variables(testvar CMAKE_VERSION)
cmake_print_properties(TARGETS app gecko PROPERTIES 
  TYPE 
  # ALIASED_TARGET
)
