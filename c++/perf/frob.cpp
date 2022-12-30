// For best results use `sudo cpupower frequency-set -g performance` first.
// Collect JSON results using `bin/perf/frobPerf --benchmark_format=json`.

#include <memory>
#include <random>
#include <benchmark/benchmark.h>

#include "Frob.h"


using frob::Frob;


#define BENCHMARK_SAMPLES(func, ...)                                           \
        BENCHMARK(func)                                                        \
          ->Repetitions(20)                                                    \
          ->Arg(16384);


static void
frobnosticate(benchmark::State& state) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<uint32_t> dis{0, 299};

  std::vector<Frob> frobs;
  frobs.reserve(static_cast<size_t>(state.range(0)));
  for (int64_t i = 0, end = state.range(0); i < end; ++i) {
    uint8_t a  = static_cast<uint8_t>(dis(gen));
    uint32_t b = dis(gen);
    uint8_t c  = static_cast<uint8_t>(dis(gen));
    uint16_t d = static_cast<uint16_t>(dis(gen));
    double e   = dis(gen);
    double f   = dis(gen);
    double g   = dis(gen);
    double h   = dis(gen);
    frobs.emplace_back(a, b, c, d, e, f, g, h);
  }

  uint32_t result = 1;

  // Each iteration of this loop is tracked and timed by the framework.
  for (auto _ : state) {
    for (const auto& frob : frobs) {
      result = frob.frobnicate(result, result);
    }
    benchmark::DoNotOptimize(result);
  }

  state.SetItemsProcessed(state.range(0) * state.iterations());
  state.SetComplexityN(state.range(0));
}


BENCHMARK_SAMPLES(frobnosticate);

BENCHMARK_MAIN();
