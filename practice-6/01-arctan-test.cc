#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <type_traits>
#include <pthread.h>
#include <x86intrin.h>

/// MyActan(x, 0) = 0
extern "C" float __cdecl MyArctan(float x, uint32_t n);

auto measure(std::invocable auto workload) {
  static unsigned int dummy;
  auto start = __rdtscp(&dummy);
  workload();
  auto end = __rdtscp(&dummy);
  return end - start;
}

int main() {
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
  for (auto arg : args) {
    const float realValue = std::atan(arg);
    std::cout << "Calculating arctan(" << arg << ")" << std::endl;
    for (uint32_t summands = 0; summands <= 100; summands += 20) {
      auto result = MyArctan(arg, summands);
      std::cout
        << "    With " << summands << " summands: "
        << result
        << " (error = " << std::fabs(result - realValue) << ")"
        << std::endl;
    }
  }
  for (auto arg : args) {
    for (uint32_t summands = 0; summands <= 100; summands += 20) {
      constexpr int REPETIIONS = 1000;
      std::vector<double> measurements{1000, 0};
      auto result = MyArctan(arg, summands);
      std::cout
        << "    With " << summands << " summands: "
        << result
        << " (error = " << std::fabs(result - realValue) << ")"
        << std::endl;
    }
  }
  // TODO: calculate time with rdtscp
}
