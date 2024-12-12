#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <ranges>
#include <queue>
#include <cassert>
#include <cstring>
#include <x86intrin.h>

#include "lzw-baseline.hh"

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

int main(int argc, char** argv) {
  {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  }

  std::cout << "Running " << argv[0] << std::endl;
}

