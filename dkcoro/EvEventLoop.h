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

  void Run();

  ~EvEventLoop();

 private:
  EvEventLoop();

  event_base* eventBase = nullptr;

  DK_DECLARE_UNCOPYABLE(EvEventLoop);
};

}  // namespace dkcoro
