#include "semaphore.h"
#include <sched.h>
#include <stdio.h>
#include <thread>

using namespace threadlib;

semaphore_t sem(0);

void test_sem_wait_1() {
  sem.wait();
  printf("Thread 1 done\n");
}

void test_sem_wait_2() {
  sem.wait();
  printf("Thread 2 done\n");
}

void test_sem_signal() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  sem.signal();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  sem.signal();
}

namespace threadlib {
  void sched() {
    sched_yield();
  }
}

int main() {
  std::thread t1(test_sem_wait_1);
  std::thread t2(test_sem_wait_2);
  std::thread t3(test_sem_signal);
  t1.join();
  t2.join();
  t3.join();
  printf("ok\n");
}
