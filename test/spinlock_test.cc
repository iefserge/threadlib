#include <sched.h>
#include "spinlock.h"
#include "mutex.h"
#include "recursive_mutex.h"
#include <stdio.h>

using namespace threadlib;

void test_spinlock() {
  spinlock_t sp1;
  sp1.lock();
  sp1.unlock();
  sp1.lock();
  sp1.unlock();
}

namespace threadlib {
  void sched() {
    sched_yield();
  }
}

int main() {
  test_spinlock();
  printf("ok\n");
}
