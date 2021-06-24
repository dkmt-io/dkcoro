/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "uncopyable.h"

#include <functional>
#include <memory>

namespace dkcoro {  //

class timer {
 public:
  typedef std::function<void()> callback;

  struct options {
    timer::callback cb;
    uint64_t delay = 0;
    bool repeat = false;
  };

  virtual bool start() = 0;

  virtual bool stop() = 0;

  virtual ~timer() {}

 protected:
  timer();

 private:
  DK_DECLARE_UNCOPYABLE(timer);
};

}  // namespace dkcoro