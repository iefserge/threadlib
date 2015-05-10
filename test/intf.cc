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
}
