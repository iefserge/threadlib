#include <assert.h>
#include <thread>

using namespace std;

namespace threadlib {
  void libassert(int expr) {
    assert(expr);
  }

  void wait_pause() {
    asm volatile("pause" : : : "memory");
  }

  uint32_t get_thread_id() {
    return std::hash<std::thread::id>()(std::this_thread::get_id());
  }

  uint64_t get_time_microseconds() {
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(time).count();
  }
}
