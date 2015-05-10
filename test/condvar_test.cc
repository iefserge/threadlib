#include "condvar.h"
#include <sched.h>
#include <stdio.h>
#include <thread>

using namespace threadlib;

namespace threadlib {
  void sched() {
    sched_yield();
  }
}

bool is_ready(false);
mutex_t m;
condvar_t cv;

void test() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m.lock();
  is_ready = true;
  cv.signal();
  m.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m.lock();
  is_ready = true;
  cv.signal();
  m.unlock();
}

void test_t1() {
  m.lock();
  while (!is_ready) {
    cv.wait(&m);
  }
  is_ready = false;
  m.unlock();
  printf("t1 done\n");
}

void test_t2() {
  m.lock();
  while (!is_ready) {
    cv.wait(&m);
  }
  is_ready = false;
  m.unlock();
  printf("t2 done\n");
}

int main() {
  std::thread t(test);
  std::thread t1(test_t1);
  std::thread t2(test_t2);

  t.join();
  t1.join();
  t2.join();
  printf("ok\n");
}
