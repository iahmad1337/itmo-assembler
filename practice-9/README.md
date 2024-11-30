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
```
TODO
```
