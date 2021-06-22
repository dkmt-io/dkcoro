/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "Uncopyable.h"

#include <functional>
#include <memory>

namespace dkcoro {  //

class Timer {
 public:
  typedef std::function<void()> Callback;

  struct Options {
    Timer::Callback cb;
    uint64_t delay = 0;
    bool repeat = false;
  };

  virtual bool Start() = 0;

  virtual bool Stop() = 0;

  virtual ~Timer() {}

 protected:
  Timer();

 private:
  DK_DECLARE_UNCOPYABLE(Timer);
};

}  // namespace dkcoro