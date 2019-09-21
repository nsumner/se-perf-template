
add_library(executor
  empty.cpp
)

target_include_directories(executor
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(executor
  PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

