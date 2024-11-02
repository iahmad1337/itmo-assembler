# Measurements
- Make sure that Turbo/power saving is turned off. Tutorial for linux: https://askubuntu.com/a/620114 .
  TL;DR: `echo "1" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo`
  Don't forget to turn it back up (with `echo "0"...`)
- OS will affect the measurements with preemption, but we can't do anything
  about it
- don't use the usual timing techniques because they rely on visiting kernel
  space. Use `rtdscp` instead.
- it might be a good idea to lock a CPU core (using `pthread_<bla-bla>setaffinity<bla-bla>`)

## Results

Tested on [8265u](https://en.wikichip.org/wiki/intel/core_i5/i5-8265u) with
turbo turned off and the process assigned to one cpu.
```
Calculating arctan(-1)
    With 0 summands: 0 (error = 0.785398)
    With 20 summands: -0.772906 (error = 0.0124922)
    With 40 summands: -0.779149 (error = 0.00624907)
    With 60 summands: -0.781232 (error = 0.00416642)
    With 80 summands: -0.782273 (error = 0.00312489)
    With 100 summands: -0.782898 (error = 0.00249994)
Calculating arctan(-0.707107)
    With 0 summands: 0 (error = 0.61548)
    With 20 summands: -0.61548 (error = 0)
    With 40 summands: -0.61548 (error = 0)
    With 60 summands: -0.61548 (error = 0)
    With 80 summands: -0.61548 (error = 0)
    With 100 summands: -0.61548 (error = 0)
Calculating arctan(-0.57735)
    With 0 summands: 0 (error = 0.523599)
    With 20 summands: -0.523599 (error = 0)
    With 40 summands: -0.523599 (error = 0)
    With 60 summands: -0.523599 (error = 0)
    With 80 summands: -0.523599 (error = 0)
    With 100 summands: -0.523599 (error = 0)
Calculating arctan(0)
    With 0 summands: 0 (error = 0)
    With 20 summands: 0 (error = 0)
    With 40 summands: 0 (error = 0)
    With 60 summands: 0 (error = 0)
    With 80 summands: 0 (error = 0)
    With 100 summands: 0 (error = 0)
Calculating arctan(0.57735)
    With 0 summands: 0 (error = 0.523599)
    With 20 summands: 0.523599 (error = 0)
    With 40 summands: 0.523599 (error = 0)
    With 60 summands: 0.523599 (error = 0)
    With 80 summands: 0.523599 (error = 0)
    With 100 summands: 0.523599 (error = 0)
Calculating arctan(0.707107)
    With 0 summands: 0 (error = 0.61548)
    With 20 summands: 0.61548 (error = 0)
    With 40 summands: 0.61548 (error = 0)
    With 60 summands: 0.61548 (error = 0)
    With 80 summands: 0.61548 (error = 0)
    With 100 summands: 0.61548 (error = 0)
Calculating arctan(1)
    With 0 summands: 0 (error = 0.785398)
    With 20 summands: 0.772906 (error = 0.0124922)
    With 40 summands: 0.779149 (error = 0.00624907)
    With 60 summands: 0.781232 (error = 0.00416642)
    With 80 summands: 0.782273 (error = 0.00312489)
    With 100 summands: 0.782898 (error = 0.00249994)

Starting the measurements (1000000 repetitions per call)
    With 1 summands:  avg = 58.1368 +- 125.793 (stddev)
    With 2 summands:  avg = 77.3508 +- 90.4378 (stddev)
    With 4 summands:  avg = 93.1116 +- 104.297 (stddev)
    With 8 summands:  avg = 129.185 +- 144.988 (stddev)
    With 16 summands:  avg = 200.618 +- 119.878 (stddev)
    With 32 summands:  avg = 344.071 +- 249.102 (stddev)
    With 64 summands:  avg = 621.177 +- 230.03 (stddev)
    With 128 summands:  avg = 1187.98 +- 357.592 (stddev)
    With 256 summands:  avg = 2312.92 +- 599.171 (stddev)
    With 512 summands:  avg = 4537.99 +- 721.474 (stddev)
    With 1024 summands:  avg = 9002.75 +- 863.02 (stddev)
```

Judging by the measurements, we have ~9 ticks per summation loop in `MyArctan`.
