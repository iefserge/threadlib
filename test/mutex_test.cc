#include "mutex.h"
#include <sched.h>
#include <stdio.h>
#include <thread>

using namespace threadlib;

mutex_t m;
mutex_t* sched_unlock_mutex = nullptr;
int value = 0;

void test_1() {
  bool t;
  for (int i = 0; i < 100000; ++i) {
    m.lock();
    t = m.try_lock();
    libassert(t == false);
    value--;
    m.unlock();
  }
  printf("Thread 1 done\n");
}

void test_2() {
  for (int i = 0; i < 100000; ++i) {
    m.lock();
    if ((i % 1000) == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    value++;
    m.unlock();
  }
  printf("Thread 2 done\n");
}

void test_3() {
  mutex_t m;
  sched_unlock_mutex = &m;
  m.lock();
  m.lock();
}

namespace threadlib {
  void sched() {
    sched_yield();
    if (sched_unlock_mutex) {
      sched_unlock_mutex->unlock();
      sched_unlock_mutex = nullptr;
    }
  }
}

int main() {
  std::thread t1(test_1);
  std::thread t2(test_2);
  t1.join();
  t2.join();
  libassert(value == 0);
  test_3();
  printf("test 3 done\n");
  printf("ok\n");
}
