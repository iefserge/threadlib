## C++ synchronization primitives

OS-independent synchronization primitives written in C++11 and used in runtime.js.

- Spinlock
- Mutex
- Recursive mutex
- Semaphore
- Condition Variable

See tests for usage https://github.com/iefserge/threadlib/tree/master/test

Operating system interface:

```c++
namespace threadlib {
  // reschedule another thread
  void sched();
  
  // called in busy-wait loops
  void wait_pause();
  
  // assertion function
  void libassert(int);
  
  // get current thread ID
  uint32_t get_thread_id();
  
  // get current time in microseconds
  uint64_t get_time_microseconds();
}
```
