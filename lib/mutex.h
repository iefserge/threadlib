#pragma once

#include <stdint.h>
#include "nocopy.h"
#include "spinlock.h"
#include "intf.h"

namespace threadlib {
  class mutex_t : private spinlock_t {
    public:
      mutex_t() {}

      void lock() {
        while (!spinlock_t::try_lock()) {
          sched();
        }
      }

      bool try_lock() {
        return spinlock_t::try_lock();
      }

      void unlock() {
        spinlock_t::unlock();
      }
    private:
      THREAD_LIB_DELETE_COPY_AND_ASSIGN(mutex_t);
  };
}
