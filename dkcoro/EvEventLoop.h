/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "EventLoop.h"
#include "Uncopyable.h"

#include <event2/event.h>

#include <memory>

namespace dkcoro {

class EvEventLoop final : public EventLoop {
 public:
  static std::shared_ptr<EvEventLoop> Create();

  virtual void Run() override;

  virtual std::shared_ptr<Timer> SetTimeout(
    const Timer::Callback&, uint64_t /* clang-format off */
  ) override; /* clang-format on */

  virtual std::shared_ptr<Timer> SetInterval(
    const Timer::Callback&, uint64_t /* clang-format off */
  ) override; /* clang-format on */

  virtual ~EvEventLoop();

 protected:
  EvEventLoop();

  event_base* eventBase = nullptr;

 private:
  DK_DECLARE_UNCOPYABLE(EvEventLoop);
};

}  // namespace dkcoro
