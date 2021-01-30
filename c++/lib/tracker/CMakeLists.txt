
add_library(tracker INTERFACE)

target_include_directories(tracker
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

