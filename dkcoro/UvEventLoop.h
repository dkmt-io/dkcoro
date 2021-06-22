/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "EventLoop.h"
#include "Timer.h"
#include "Uncopyable.h"

#include <uv.h>

#include <memory>

namespace dkcoro {

class UvEventLoop final : public EventLoop {
 public:
  static std::shared_ptr<UvEventLoop> Create();

  virtual void Run() override;

  virtual std::shared_ptr<Timer> SetTimeout(
    const Timer::Callback&, uint64_t /* clang-format off */
  ) override; /* clang-format on */

  virtual std::shared_ptr<Timer> SetInterval(
    const Timer::Callback&, uint64_t /* clang-format off */
  ) override; /* clang-format on */

  virtual ~UvEventLoop();

 protected:
  UvEventLoop();

  uv_loop_t uvLoop;

 private:
  DK_DECLARE_UNCOPYABLE(UvEventLoop);
};

}  // namespace dkcoro
