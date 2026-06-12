cmake_minimum_required(VERSION 4.1)

list(APPEND CMAKE_MESSAGE_CONTEXT app)

add_executable(app)

target_sources(app
  PRIVATE
    src/main.cpp
)

target_sources(app
  PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
)

# target_include_directories(app
#   PUBLIC
#     include
#     src
# )

set_target_properties(app PROPERTIES 
  # CXX_STANDARD 23
  VERIFY_INTERFACE_HEADER_SETS ON
  #   CXX_STANDARD_REQUIRED ON
  #   CXX_EXTENSIONS OFF
  #   CXX_MODULE_STD 1
)

target_compile_features(app PRIVATE cxx_std_23)

target_compile_options(app PRIVATE 
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  # $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors -Werror>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Wfatal-errors>
  # -stdlib=libc++
)
