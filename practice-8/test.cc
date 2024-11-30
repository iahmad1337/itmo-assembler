#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <ranges>
#include <queue>
#include <cassert>
#include <random>
#include <numeric>
#include <algorithm>
#include <x86intrin.h>

extern "C" void __cdecl MaxElementSigned(int8_t* dst, const int8_t* src, uint32_t n);

auto measure(std::invocable auto workload) {
  static unsigned int dummy;
  auto start = __rdtscp(&dummy);
  workload();
  auto end = __rdtscp(&dummy);
  return end - start;
}

double heap_sum(const std::ranges::range auto& values) {
  assert (!std::ranges::empty(values));
  std::priority_queue q{std::greater<double>{}, values};
  while (q.size() > 1) {
    auto top = q.top();
    q.pop();
    auto top2 = q.top();
    q.pop();
    q.push(top + top2);
  }
  return q.top();
}

auto aggregate(const std::ranges::range auto& values) {
  struct {
    double avg = 0;
    double stddev = 0;
  } statistics;

  statistics.avg = heap_sum(values) / std::ranges::size(values);
  for (const auto& value : values) {
    statistics.stddev += (value - statistics.avg) * (value - statistics.avg) / std::ranges::size(values);
  }

  statistics.stddev = std::sqrt(statistics.stddev);

  return statistics;
}

#define print_sequence(a) \
  { \
    std::cout << "Printing the array "#a": { "; \
    for (auto& e : a) std::cout << (int)e << " "; \
    std::cout << "}" << std::endl; \
  }

int main() {
  {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  }


  const size_t N = 3 * 4;  // must be divisable by 4
  std::vector<int8_t> a(N);
  std::vector<int8_t> b(N);

  auto rng = std::mt19937_64{};
  auto distrib = std::uniform_int_distribution<int8_t>{};
  auto generator = [&] { return distrib(rng); };

  std::generate(a.begin(), a.end(), generator);
  std::generate(b.begin(), b.end(), generator);

  auto golden = a;

  for (size_t i = 0; i < N; i++) {
    golden[i] = std::max(a[i], b[i]);
  }

  auto result = a;
  MaxElementSigned(result.data(), b.data(), N);

  print_sequence(a);
  print_sequence(b);
  print_sequence(golden);
  print_sequence(result);

  assert(result == golden);

  // std::cout.precision(6);
  // for (auto arg : args) {
  //   const float realValue = std::atan(arg);
  //   std::cout << "Calculating arctan(" << arg << ")" << std::endl;
  //   for (uint32_t summands = 0; summands <= 100; summands += 20) {
  //     auto result = MyArctan(arg, summands);
  //     std::cout
  //       << "    With " << summands << " summands: "
  //       << result
  //       << " (error = " << std::fabs(result - realValue) << ")"
  //       << std::endl;
  //   }
  // }
  // constexpr int REPETIIONS = 1'000'000;
  // std::vector<double> measurements{REPETIIONS, 0};
  //
  // std::cout << "\n\n\nStarting the measurements (" << REPETIIONS << " repetitions per call)" << std::endl;
  // for (uint32_t summands = 1; summands <= 1024; summands *= 2) {
  //   measurements.assign(REPETIIONS, 0);
  //   for (auto& m : measurements) {
  //     m = measure([&] { MyArctan(args[1], summands); });
  //   }
  //   auto statistics = aggregate(measurements);
  //   std::cout
  //     << "    With " << summands << " summands: "
  //     << " avg = " << statistics.avg
  //     << " +- " << statistics.stddev << " (stddev)"
  //     << std::endl;
  // }
}
