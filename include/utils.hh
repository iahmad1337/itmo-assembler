#pragma once

#include <vector>
#include <cmath>
#include <pthread.h>
#include <queue>
#include <cassert>
#include <cstring>
#include <x86intrin.h>
#include <ranges>
#include <sstream>

#if defined(__clang__)
#define __cdecl __cdecl
#elif defined(__GNUC__) || defined(__GNUG__)
#define __cdecl __attribute__((__cdecl__))
#endif

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

struct TStatistics {
  /// Percentiles
  double p50 = 0;   // = median
  double p90 = 0;
  double p99 = 0;
  double p9999 = 0;

  /// Basic stats
  double min = 0;
  double max = 0;
  double avg = 0;
  double stddev = 0;

  std::string ToJson() const {
#define FIELD(x) "\""#x"\":" << x << ","
#define LAST_FIELD(x) "\""#x"\":" << x
    std::stringstream ss;
    ss << "{"
      << FIELD(min)
      << FIELD(p50)
      << FIELD(p90)
      << FIELD(p99)
      << FIELD(p9999)
      << FIELD(max)
      << FIELD(avg)
      << LAST_FIELD(stddev)
      << "}";
#undef FIELD
    return ss.str();
  }
};

TStatistics aggregate(const std::ranges::range auto& values) {
  assert(!std::ranges::empty(values));

  TStatistics statistics;


  // min & max
  auto [minIt, maxIt] = std::minmax_element(std::begin(values), std::end(values));
  statistics.min = *minIt;
  statistics.max = *maxIt;

  // percentiles
  auto size = std::ranges::size(values);
  auto toIndex = [size] (auto quantile) { return std::lround(std::lerp(1, size, quantile)) - 1; };
  auto mutableCopy = values;
  std::sort(std::begin(mutableCopy), std::end(mutableCopy));
  statistics.p50 = mutableCopy[toIndex(0.5)];
  statistics.p90 = mutableCopy[toIndex(0.90)];
  statistics.p99 = mutableCopy[toIndex(0.99)];
  statistics.p9999 = mutableCopy[toIndex(0.9999)];

  // avg & stddev
  statistics.avg = heap_sum(values) / size;
  statistics.stddev = std::sqrt(
    heap_sum(
      values,
      [&] (double v) { return (v - statistics.avg) * (v - statistics.avg) / std::ranges::size(values); }
    )
  );

  return statistics;
}

void FixateCore(auto id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(id, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
}
