#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <ranges>
#include <queue>
#include <cassert>
#include <cstring>
#include <x86intrin.h>

#if defined(__clang__)
#define __cdecl __cdecl
#elif defined(__GNUC__) || defined(__GNUG__)
#define __cdecl __attribute__((__cdecl__))
#endif

/// MyActan(x, 0) = 0
extern "C" uint32_t __cdecl MyStrlen(const char* c_str);

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


  const char* args[] = {
    "",
    "h",
    "ha",
    "hah",
    "haha",
    "hahahaha",
    "hahahahah",
    "hahahahaha",
  };
  std::cout << "Testing regular args (" << sizeof(args) / sizeof(const char*) << " samples)" << std::endl;

  size_t errors = 0;
  for (auto arg : args) {
    const auto realAnswer = std::strlen(arg);
    const auto myAnswer = MyStrlen(arg);
    errors += myAnswer != realAnswer;
  }

  if (errors > 0) {
    std::cerr << "Encountered " << errors << " errors" << std::endl;
    return 1;
  }

  std::string longStrings[] = {
    std::string(1000, 'a'),
    std::string(10000, 'b'),
    std::string(999, 'b'),
    std::string(998, 'b'),
    std::string(99999, 'b'),
    std::string(100001, 'b'),

  };
  std::cout << "Testing long strings (" << sizeof(longStrings) / sizeof(std::string) << " samples)" << std::endl;
  errors = 0;
  for (auto arg : longStrings) {
    const auto realAnswer = std::strlen(arg.c_str());
    const auto myAnswer = MyStrlen(arg.c_str());
    errors += myAnswer != realAnswer;
  }

  if (errors > 0) {
    std::cerr << "Encountered " << errors << " errors" << std::endl;
    return 1;
  }

  constexpr int REPETIIONS = 10;
  std::vector<double> measurements{REPETIIONS, 0};

  std::cout << "\n\n\nStarting the measurements (" << REPETIIONS << " repetitions per call)" << std::endl;
  for (uint32_t stringLength = 1; stringLength <= 100'000'000; stringLength *= 10) {
    std::string sample = std::string(stringLength + 1, 'a');

    // touch every char to minimize pagefaults
    bool change = false;
    for (auto& c : sample) {
      c = change ? 'b' : 'a';
      change = !change;
    }

    assert(*sample.end() == '\0');
    measurements.assign(REPETIIONS, 0);
    for (auto& m : measurements) {
      m = measure([&] { MyStrlen(sample.c_str()); });
    }
    auto statistics = aggregate(measurements);
    std::cout
      << "    With " << stringLength << " chars: "
      << " avg = " << statistics.avg
      << " +- " << statistics.stddev << " (stddev)"
      << std::endl;
  }
}

