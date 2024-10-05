#include "nth-prime.h"

#include <limits.h>

int NthPrime(int n) {
  if (n < 2) {
    return -1;
  }
  int primeIndex = 0;
  for (int i = 2; i != INT_MAX ;i++) {
    _Bool isPrime = 1;
    for (int j = 2; j * j <= i && j * j > 0; j++) {
      if (i % j == 0) {
        isPrime = 0;
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
