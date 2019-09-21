set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/perf)


add_executable(executorPerf executor.cpp)

set_target_properties(executorPerf
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
  PREFIX ""
)
target_link_libraries(executorPerf
  executor
  benchmark::benchmark_main
  ${CMAKE_THREAD_LIBS_INIT}
)


add_executable(frobPerf frob.cpp)

set_target_properties(frobPerf
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
  PREFIX ""
)
target_link_libraries(frobPerf
  frob
  benchmark::benchmark_main
  ${CMAKE_THREAD_LIBS_INIT}
)


add_executable(trackerPerf tracker.cpp)

set_target_properties(trackerPerf
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
  PREFIX ""
)
target_link_libraries(trackerPerf
  tracker
  benchmark::benchmark_main
  ${CMAKE_THREAD_LIBS_INIT}
)


