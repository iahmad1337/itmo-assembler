#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

/// MyActan(x, 0) = 0
extern "C" float MyArctan(float x, uint32_t n);

int main() {
  float args[] = {
    -1,
    sqrtf(-0.5),
    sqrtf(-0.33333333),
    0,
    sqrtf( 0.33333333),
    sqrtf(0.5),
    1,
  };
  std::cout.precision(6);
  for (auto arg : args) {
    std::cout << "Calculating arctan(" << arg << ")" << std::endl;
    for (uint32_t summands = 0; summands <= 100; summands += 20) {
      std::cout << "    With " << summands << " summands: " << MyArctan(arg, summands) << std::endl;
    }
  }
}
