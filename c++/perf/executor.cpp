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


static void
executeTasks(benchmark::State& state) {
  uint32_t result;

  auto createTask = [&result] (uint32_t kind) -> std::unique_ptr<Task> {
    switch (kind) {
      case 0: return std::make_unique<Task1>(result);
      case 1: return std::make_unique<Task2>(result);
      case 2: return std::make_unique<Task3>(result);
    }
    __builtin_unreachable();
  };
  
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<uint32_t> dis{0, 2};

  const size_t workloadSize = static_cast<size_t>(state.range(0));
  std::vector<std::unique_ptr<Task>> taskPool(workloadSize);
  for (size_t i = 0; i < workloadSize; ++i) {
    taskPool[i] = createTask(dis(gen));
  }

  std::vector<Task*> tasks(workloadSize);
  std::transform(taskPool.begin(), taskPool.end(), tasks.begin(),
    [] (auto& task) { return task.get(); });

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
