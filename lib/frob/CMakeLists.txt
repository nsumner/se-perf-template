
add_library(frob
  empty.cpp
)

target_include_directories(frob
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(frob
  PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

