# Task
Do the [arctan](../practice-6) exercise with SSE instead of FPU.

Subtasks:
1. Do the serial version (one summand at a time)
2. Do a parallel "streaming" version (four summands at a time)
3. Integer arithmetic: `strlen(const char*)`. You can bypass the string bounadary. It's important that short shouldn't
    3.1. SSE
    3.2. AVX
    3.3. (Optional) AVX2
    3.4. How to not bypass the string boundary? Hint: there's something you need
    to know about memory allocation and how to bypass the SEGFAULT on boundary
    passage

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

### 1. Serial SSE
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

### 2. Parallel SSE
Note: xmm registers are independent of FPU, unlike mm registers!

According to uops.info, `pshufd` has quite a low latency (1 tick)

...
do the horizontal add at the end

TODO: make boundaries obrabotka

How to deal with the end move?
```
TODO
```

# Notes
- Use `PSHUFD` instead of `SHUFPS`, as the latter doesn't do exactly what you
  want when the operands are different
