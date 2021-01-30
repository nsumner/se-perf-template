
add_library(frob INTERFACE)

target_include_directories(frob
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

