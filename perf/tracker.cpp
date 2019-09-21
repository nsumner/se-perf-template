// For best results use `sudo cpupower frequency-set -g performance` first.
// Collect JSON results using `bin/perf/trackerPerf --benchmark_format=json`.

#include <random>
#include <benchmark/benchmark.h>

#include "Tracker.h"

using tracker::EntityTracker;
using tracker::Location;
using tracker::ActionPlan;


#define BENCHMARK_SAMPLES(func, ...)                                           \
        BENCHMARK(func)                                                        \
          ->Repetitions(20)                                                    \
          ->Arg(16384);


constexpr size_t maxElementCount = 16384;


std::vector<Location> randomLocations(maxElementCount);
std::vector<std::string> randomNames(maxElementCount);
std::vector<ActionPlan> randomPlans(maxElementCount);

static struct Initializer {
  Initializer() {
    // Set up random values that can be shared across all benchmarks
    std::random_device rd;
    std::mt19937 gen{rd()};
    using Limits = std::numeric_limits<uint32_t>;
    std::uniform_int_distribution<uint32_t> dis{Limits::min(), Limits::max()};


    for (auto& location : randomLocations) {
      location.x = dis(gen);
      location.y = dis(gen);
    }
    for (auto& name : randomNames) {
      const char shortName[1] = { static_cast<char>(dis(gen)) };
      name = shortName;
    }
    for (auto& plan : randomPlans) {
      for (auto& element : plan.secretPlan) {
        element = dis(gen);
      }
    }
  }
} globalDataInitializerObject;


static void
fillTracker(EntityTracker& tracker, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    tracker.addEntity(randomLocations[i], randomNames[i], randomPlans[i]);
  }
}


static bool
returnsTrue(Location location) {
  return true;
}


static bool
returnsTrueInLowQuadrant(Location location) {
  constexpr auto bound = std::numeric_limits<uint32_t>::max() / 2;
  return (location.x < bound) && (location.y < bound);
}


static void
countTrue(benchmark::State& state) {
  EntityTracker tracker;
  fillTracker(tracker, state.range(0));

  // Each iteration of this loop is tracked and timed by the framework.
  for (auto _ : state) {
    benchmark::DoNotOptimize(tracker.countDangerous(returnsTrue));
  }

  state.SetItemsProcessed(state.range(0) * state.iterations());
  state.SetComplexityN(state.range(0));
}


static void
countQuadrant(benchmark::State& state) {
  EntityTracker tracker;
  fillTracker(tracker, state.range(0));

  // Each iteration of this loop is tracked and timed by the framework.
  for (auto _ : state) {
    benchmark::DoNotOptimize(tracker.countDangerous(returnsTrueInLowQuadrant));
  }

  state.SetItemsProcessed(state.range(0) * state.iterations());
  state.SetComplexityN(state.range(0));
}


static void
checkSecrets(benchmark::State& state) {
  EntityTracker tracker;
  fillTracker(tracker, state.range(0));

  // Each iteration of this loop is tracked and timed by the framework.
  for (auto _ : state) {
    uint32_t mark = 0;
    auto check = [&mark] (const ActionPlan& plan) {
      mark = std::accumulate(plan.secretPlan.begin(), plan.secretPlan.end(), mark,
        [] (auto sofar, auto byte) { return 3 * sofar + byte; });
    };
    tracker.checkPlans(check);
    benchmark::DoNotOptimize(mark);
  }

  state.SetItemsProcessed(state.range(0) * state.iterations());
  state.SetComplexityN(state.range(0));
}


BENCHMARK_SAMPLES(countTrue);
BENCHMARK_SAMPLES(countQuadrant);
BENCHMARK_SAMPLES(checkSecrets);

BENCHMARK_MAIN();
