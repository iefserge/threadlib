#pragma once

#include <stdint.h>
#include "nocopy.h"
#include "intf.h"

namespace threadlib {
  class semaphore_t {
    public:
      volatile uint32_t count_;
      semaphore_t(uint32_t initial_count) : count_(initial_count) {}

      bool try_wait() {
        uint32_t count;

        while ((count = count_) > 0) {
          if (__sync_val_compare_and_swap(&count_, count, count - 1) == count) {
            return true;
          }
        }

        return false;
      }

      void wait() {
        while (!try_wait()) {
          sched();
        }
      }

      void signal() {
        uint32_t count;

        do {
          count = count_;
        } while (__sync_val_compare_and_swap(&count_, count, count + 1) != count);
      }
    private:
      THREAD_LIB_DELETE_COPY_AND_ASSIGN(semaphore_t);
  };
}
