
add_library(executor INTERFACE)

target_include_directories(executor
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

