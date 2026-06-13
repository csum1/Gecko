cmake_minimum_required(VERSION 4.1)
# must be set before project() call
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ON)
# THIS IS CRITICAL - Enable experimental import std support
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

# CMAKE_CURRENT_SOURCE_DIR : directory of individual CMakeLists.txt
# PROJECT_SOURCE_DIR : directory of project
list(APPEND CMAKE_MESSAGE_CONTEXT Gui)
message(STATUS "Starting to create")

project(Gui 
  DESCRIPTION "A GUI for applications"
  LANGUAGES CXX
  VERSION 1.0 
)

include(CTest)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# set(CMAKE_CXX_MODULE_STD ON)
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# set(CMAKE_CXX_FLAGS "-stdlib=libc++ -Wno-reserved-module-identifier")
# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Debug)
# endif()

add_subdirectory(app)
add_subdirectory(gui)
add_subdirectory(test)

target_link_libraries(gecko PRIVATE glfw)
target_link_libraries(app PRIVATE gecko)

# get info of targets
# TARGETS, SOURCES, DIRECTORIES, TESTS, CACHE_ENTRIES
set(testvar "mytest")

include(CMakePrintHelpers)

cmake_print_variables(testvar CMAKE_VERSION)

cmake_print_properties(TARGETS app gecko cpp PROPERTIES 
  TYPE 
  # ALIASED_TARGET
)
