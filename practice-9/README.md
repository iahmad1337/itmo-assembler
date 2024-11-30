# Task

# Measurements
- Make sure that Turbo/power saving is turned off. Tutorial for linux: https://askubuntu.com/a/620114 .
  TL;DR: `echo "1" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo`
  Don't forget to turn it back up (with `echo "0"...`)
- OS will affect the measurements with preemption, but we can't do anything
  about it

## Results

Tested on [8265u](https://en.wikichip.org/wiki/intel/core_i5/i5-8265u) with
turbo turned off and the process assigned to one cpu.

### Serial SSE
```
TODO
```

### Parallel SSE
Note: xmm registers are independent of FPU, unlike mm registers!

Plan:
1. numerators are in xmm0, denominators are in xmm1
2. do the loop by steps of 4 (i = 0; i < n; i += 4), until the desired value is in xmm3
3. Depending on n % 4 value, load the corresponding float from xmm0 (0-31,
   32-63, 64-95 or 96-127 bits respectively). Or it just may be a shuffle
4.
```
TODO
```
