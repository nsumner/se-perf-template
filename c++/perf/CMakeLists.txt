set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/perf)


add_executable(executorPerf)
target_sources(executorPerf
  PRIVATE
    executor.cpp
)

target_compile_features(executorPerf PUBLIC cxx_std_20)
set_target_properties(executorPerf PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX ""
)
target_link_libraries(executorPerf
  PRIVATE
    executor
    benchmark::benchmark_main
    ${CMAKE_THREAD_LIBS_INIT}
)


add_executable(frobPerf)
target_sources(frobPerf
  PRIVATE
    frob.cpp
)

target_compile_features(frobPerf PUBLIC cxx_std_20)
set_target_properties(frobPerf  PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX ""
)
target_link_libraries(frobPerf
  PRIVATE
    frob
    benchmark::benchmark_main
    ${CMAKE_THREAD_LIBS_INIT}
)


add_executable(trackerPerf)
target_sources(trackerPerf
  PRIVATE
    tracker.cpp
)

target_compile_features(trackerPerf PUBLIC cxx_std_20)
set_target_properties(trackerPerf PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX ""
)
target_link_libraries(trackerPerf
  PRIVATE
    tracker
    benchmark::benchmark_main
    ${CMAKE_THREAD_LIBS_INIT}
)


