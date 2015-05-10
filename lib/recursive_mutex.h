#pragma once

#include <stdint.h>
#include "nocopy.h"
#include "spinlock.h"
#include "intf.h"

namespace threadlib {
  class recursive_mutex_t : private spinlock_t {
    public:
      recursive_mutex_t() : owner_(0), depth_(0) {}
      uint32_t owner_;
      uint32_t depth_;

      void lock() {
        uint32_t thread_id = get_thread_id();
        if (owner_ == thread_id) {
          ++depth_;
          return;
        }

        while (!spinlock_t::try_lock()) {
          sched();
        }

        owner_ = thread_id;
        ++depth_;
      }

      bool try_lock() {
        uint32_t thread_id = get_thread_id();
        if (owner_ == thread_id) {
          ++depth_;
          return true;
        }

        if (spinlock_t::try_lock()) {
          owner_ = thread_id;
          ++depth_;
          return true;
        }

        return false;
      }

      void unlock() {
        libassert(depth_ > 0 && "trying to unlock() unlocked recursive_mutex");
        if (--depth_ == 0) {
          owner_ = 0;
          spinlock_t::unlock();
        }
      }

    private:
      THREAD_LIB_DELETE_COPY_AND_ASSIGN(recursive_mutex_t);
  };
}
