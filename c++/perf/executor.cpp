// For best results use `sudo cpupower frequency-set -g performance` first.
// Collect JSON results using `bin/perf/executorPerf --benchmark_format=json`.

#include <memory>
#include <random>
#include <benchmark/benchmark.h>

#include "Executor.h"


using executor::Task;
using executor::Task1;
using executor::Task2;
using executor::Task3;
using executor::Executor;


#define BENCHMARK_SAMPLES(func, ...)                                           \
        BENCHMARK(func)                                                        \
          ->Repetitions(20)                                                    \
          ->Arg(16384);


constexpr size_t maxElementCount = 16384;


static void
executeTasks(benchmark::State& state) {
  uint32_t result;
  std::vector<std::unique_ptr<Task>> taskPool(300);
  for (auto i = 0; i < 100; ++i) {
    taskPool[i] = std::make_unique<Task1>(result);
  }
  for (auto i = 100; i < 200; ++i) {
    taskPool[i] = std::make_unique<Task2>(result);
  }
  for (auto i = 200; i < 300; ++i) {
    taskPool[i] = std::make_unique<Task3>(result);
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<uint32_t> dis{0, 299};

  std::vector<Task*> tasks(state.range(0));
  for (auto& task : tasks) {
    task = taskPool[dis(gen)].get();
  }

  Executor executor{tasks};

  // Each iteration of this loop is tracked and timed by the framework.
  for (auto _ : state) {
    result = 0;
    executor.execute();
    benchmark::DoNotOptimize(result);
  }

  state.SetItemsProcessed(state.range(0) * state.iterations());
  state.SetComplexityN(state.range(0));
}


BENCHMARK_SAMPLES(executeTasks);

BENCHMARK_MAIN();
