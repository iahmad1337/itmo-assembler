# Task
Do the [arctan](../practice-6) exercise with SSE instead of FPU.

Subtasks:
1. Do the serial version (one summand at a time)
2. Do a parallel "streaming" version (four summands at a time)
3. Upgrade parallel version to x64 (along with tests)
4. Integer arithmetic: `strlen(const char*)`. You can bypass the string bounadary. It's important that short shouldn't
    4.1. SSE (xmm)
    4.2. AVX (ymm)
    4.3. (Optional) AVX2
    4.4. How to not bypass the string boundary? Hint: there's something you need
    to know about memory allocation and how to bypass the SEGFAULT on boundary
    passage

- Possible solution to 3.4 is to check for the page boundary: https://stackoverflow.com/questions/37800739/is-it-safe-to-read-past-the-end-of-a-buffer-within-the-same-page-on-x86-and-x64
- Useful commands for boundary check in strlen: `pmovmskb` & `bsf`/`bsr`
- ptest

# Measurements
- Make sure that Turbo/power saving is turned off. Tutorial for linux: https://askubuntu.com/a/620114 .
  TL;DR: `echo "1" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo`
  Don't forget to turn it back up (with `echo "0"...`)
- OS will affect the measurements with preemption, but we can't do anything
  about it
- Milliseconds are the units that can be measured, that's why we need to take a
  lot of summands

## Results

Tested on [8265u](https://en.wikichip.org/wiki/intel/core_i5/i5-8265u) with
turbo turned off and the process assigned to one cpu.

### 1. Serial SSE arctan
```
Starting the measurements (1000000 repetitions per call)
    With 1 summands:  avg = 59.0447 +- 144.223 (stddev)
    With 2 summands:  avg = 72.4294 +- 125.94 (stddev)
    With 4 summands:  avg = 99.9015 +- 117.781 (stddev)
    With 8 summands:  avg = 154.16 +- 138.056 (stddev)
    With 16 summands:  avg = 260.263 +- 175.695 (stddev)
    With 32 summands:  avg = 477.765 +- 214.697 (stddev)
    With 64 summands:  avg = 911.944 +- 270.197 (stddev)
    With 128 summands:  avg = 3865.67 +- 343.731 (stddev)
    With 256 summands:  avg = 12194.9 +- 874.346 (stddev)
    With 512 summands:  avg = 15666.2 +- 935.136 (stddev)
    With 1024 summands:  avg = 22561.6 +- 727.828 (stddev)
```

More summands:
```
Starting the measurements (100 repetitions per call)
    With 1 summands:  avg = 58.62 +- 5.63166 (stddev)
    With 10 summands:  avg = 179.31 +- 3.05841 (stddev)
    With 100 summands:  avg = 1396.2 +- 2.96311 (stddev)
    With 1000 summands:  avg = 22406.1 +- 2357.76 (stddev)
    With 10000 summands:  avg = 145106 +- 3096.18 (stddev)
    With 100000 summands:  avg = 1.37602e+06 +- 25101.7 (stddev)
    With 1000000 summands:  avg = 1.36103e+07 +- 42917.2 (stddev)
    With 10000000 summands:  avg = 1.35839e+08 +- 132703 (stddev)
```

### 2. Parallel SSE arctan
Note: xmm registers are independent of FPU, unlike mm registers! So no need to
do `emms` at the end of all operations

```
Starting the measurements (100 repetitions per call)
    With 1 summands:  avg = 93.13 +- 5.70378 (stddev)
    With 10 summands:  avg = 101.81 +- 5.2606 (stddev)
    With 100 summands:  avg = 202.44 +- 3.70222 (stddev)
    With 1000 summands:  avg = 4321.24 +- 6.22916 (stddev)
    With 10000 summands:  avg = 15718.5 +- 1268.69 (stddev)
    With 100000 summands:  avg = 131305 +- 8045.43 (stddev)
    With 1000000 summands:  avg = 1.26689e+06 +- 20698.8 (stddev)
    With 10000000 summands:  avg = 1.25391e+07 +- 29916.5 (stddev)
```

### 4. strlen

#### 4.0. Non-SSE implementation
```
Starting the measurements (10 repetitions per call)
    With 1 chars:  avg = 51.6 +- 11.4996 (stddev)
    With 10 chars:  avg = 63.2 +- 12.8903 (stddev)
    With 100 chars:  avg = 280.5 +- 43.546 (stddev)
    With 1000 chars:  avg = 2306.6 +- 22.9922 (stddev)
    With 10000 chars:  avg = 22591.2 +- 24.3097 (stddev)
    With 100000 chars:  avg = 242416 +- 22666.6 (stddev)
    With 1000000 chars:  avg = 2.41891e+06 +- 239869 (stddev)
    With 10000000 chars:  avg = 2.4131e+07 +- 2.14088e+06 (stddev)
    With 100000000 chars:  avg = 2.31475e+08 +- 564357 (stddev)
```

# Notes
- Use `PSHUFD` instead of `SHUFPS`, as the latter doesn't do exactly what you
  want when the operands are different
