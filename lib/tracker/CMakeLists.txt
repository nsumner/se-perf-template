
add_library(tracker
  empty.cpp
)

target_include_directories(tracker
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(tracker
  PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

