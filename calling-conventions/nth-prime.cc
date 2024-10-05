#include "nth-prime.h"

#include <vector>
#include <limits>

int NthPrime(int n) {
  if (n < 2) {
    return -1;
  }
  int primeIndex = 0;
  for (int i = 2; i != std::numeric_limits<int>::max() ;i++) {
    bool isPrime = true;
    for (int j = 2; j * j <= i && j * j > 0; j++) {
      if (i % j == 0) {
        isPrime = false;
      }
    }
    if (isPrime) {
      primeIndex++;
      if (primeIndex == n) {
        return i;
      }
    }
  }
  return -1;
}
