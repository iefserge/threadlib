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

void test_timed() {
  uint64_t max_time = 1 * 1000 * 1000; /* 1 second in microseconds */
  m.lock();
  while (!is_ready) {
    if (!cv.timed_wait(&m, max_time)) {
      break;
    }
  }
  m.unlock();
  printf("timed done\n");
}

void test_timed_2() {
  uint64_t max_time = 2 * 1000 * 1000; /* 2 seconds in microseconds */
  m.lock();
  while (!is_ready) {
    if (!cv.timed_wait(&m, max_time)) {
      break;
    }
  }
  m.unlock();
  printf("timed done 2\n");
}

void test_timed_3() {
  uint64_t max_time = 1 * 1000 * 1000; /* 1 second in microseconds */
  m.lock();
  while (!is_ready) {
    if (!cv.timed_wait(&m, max_time)) {
      break;
    }
  }
  m.unlock();
  printf("timed done 3\n");
}

int main() {
  std::thread t(test);
  std::thread t1(test_t1);
  std::thread t2(test_t2);

  t.join();
  t1.join();
  t2.join();

  std::thread t3(test_timed);
  t3.join();

  std::thread t4(test_timed_2);
  std::thread t5(test_timed_3);
  t4.join();
  t5.join();

  printf("ok\n");
}
