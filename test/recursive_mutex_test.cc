#include "mutex.h"
#include <sched.h>
#include <stdio.h>
#include <thread>

using namespace threadlib;

mutex_t m;

void test_1() {
  bool t;
  for (int i = 0; i < 100000; ++i) {
    m.lock();
    t = m.try_lock();
    libassert(t == true);
    m.unlock();
    m.unlock();
  }
  printf("Thread 1 done\n");
}

void test_2() {
  for (int i = 0; i < 100000; ++i) {
    m.lock();
    m.lock();
    m.unlock();
    m.unlock();
  }
  printf("Thread 2 done\n");
}

namespace threadlib {
  void sched() {
    sched_yield();
  }
}

int main() {
  m.set_recursive();
  std::thread t1(test_1);
  std::thread t2(test_2);
  t1.join();
  t2.join();
  printf("ok\n");
}
