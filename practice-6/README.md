# Measurements
- Make sure that Turbo/power saving is turned off
- OS will affect the measurements with preemption, but we can't do anything
  about it
- don't use the usual timing techniques because they rely on visiting kernel
  space. Use `rtdscp` instead.
- it might be a good idea to lock a CPU core (using `pthread_<bla-bla>setaffinity<bla-bla>`)
