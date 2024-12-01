#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <ranges>
#include <queue>
#include <cassert>
#include <x86intrin.h>

#if defined(__clang__)
#define __cdecl __cdecl
#elif defined(__GNUC__) || defined(__GNUG__)
#define __cdecl __attribute__((__cdecl__))
#endif

/// MyActan(x, 0) = 0
extern "C" float __cdecl MyArctan(float x, uint32_t n);

auto measure(std::invocable auto workload) {
  static unsigned int dummy;
  auto start = __rdtscp(&dummy);
  workload();
  auto end = __rdtscp(&dummy);
  return end - start;
}

template<typename F>
double heap_sum(const std::ranges::range auto& values, F&& mapper) {
  assert (!std::ranges::empty(values));
  std::priority_queue<double, std::vector<double>, std::greater<double>> q;
  for (const auto& value : values) {
    q.push(mapper(value));
  }
  while (q.size() > 1) {
    auto top = q.top();
    q.pop();
    auto top2 = q.top();
    q.pop();
    q.push(top + top2);
  }
  return q.top();
}

double heap_sum(const std::ranges::range auto& values) {
  return heap_sum(values, [](const auto& x) { return x; });
}

auto aggregate(const std::ranges::range auto& values) {
  struct {
    double avg = 0;
    double stddev = 0;
  } statistics;

  statistics.avg = heap_sum(values) / std::ranges::size(values);
  statistics.stddev = std::sqrt(
    heap_sum(
      values,
      [&] (double v) { return (v - statistics.avg) * (v - statistics.avg) / std::ranges::size(values); }
    )
  );

  return statistics;
}

int main() {
  {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  }


  float args[] = {
    -1,
    -sqrtf(0.5),
    -sqrtf(0.33333333),
    0,
    sqrtf(0.33333333),
    sqrtf(0.5),
    1,
  };
  std::cout.precision(6);
  size_t errors = 0;
  for (auto arg : args) {
    const float realValue = std::atan(arg);
    std::cout << "Calculating arctan(" << arg << ")" << std::endl;
    for (uint32_t summands = 0; summands <= 100; summands += 20) {
      auto result = MyArctan(arg, summands);
      auto error = std::fabs(result - realValue);

      if (error > 0.01 && summands > 50) {
        errors++;
      }

      std::cout
        << "    With " << summands << " summands: "
        << result
        << " (error = " << error << ")"
        << std::endl;
    }
  }

  if (errors > 0) {
    std::cerr << "Encountered " << errors << " errors" << std::endl;
    return 1;
  }

  constexpr int REPETIIONS = 100;
  std::vector<double> measurements{REPETIIONS, 0};

  std::cout << "\n\n\nStarting the measurements (" << REPETIIONS << " repetitions per call)" << std::endl;
  for (uint32_t summands = 1; summands <= 10'000'000; summands *= 10) {
    measurements.assign(REPETIIONS, 0);
    for (auto& m : measurements) {
      m = measure([&] { MyArctan(args[1], summands); });
    }
    auto statistics = aggregate(measurements);
    std::cout
      << "    With " << summands << " summands: "
      << " avg = " << statistics.avg
      << " +- " << statistics.stddev << " (stddev)"
      << std::endl;
  }
}
