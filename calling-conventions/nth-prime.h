#ifdef __cplusplus
  #define EXTERN extern "C"
#else
  #define EXTERN extern
#endif

/// 2 is the first prime (n = 1). n > 0, nth-prime is less than INT_MAX
EXTERN int NthPrime(int n);
