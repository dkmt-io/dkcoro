/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "Timer.h"
#include "Uncopyable.h"

#include <uv.h>

#include <stdint.h>
#include <memory>

namespace dkcoro {  //

class UvTimer final : public Timer,
                      public std::enable_shared_from_this<UvTimer> {
 public:
  static std::shared_ptr<UvTimer> Create(
    const Timer::Options& options, uv_loop_t* loop  //
  );

  virtual bool Start() override;

  virtual bool Stop() override;

  virtual ~UvTimer() {}

 protected:
  UvTimer(const Timer::Options& options, uv_loop_t* loop);

  Timer::Callback cb;
  const uint64_t delay;
  bool finished = false;
  std::shared_ptr<UvTimer> self;
  const bool repeat;
  uv_loop_t* uvLoop = nullptr;
  uv_any_handle uvHandle;

  static void closeCb(uv_handle_t* handle);

  static void timerCb(uv_timer_t* timer);

 private:
  DK_DECLARE_UNCOPYABLE(UvTimer);
};

}  // namespace dkcoro