/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "Uncopyable.h"

#include <memory>

namespace dkcoro {

class EventLoop {
 public:
  static std::shared_ptr<EventLoop> Create();

  virtual void Run() = 0;

 protected:
  EventLoop() {}

  DK_DECLARE_UNCOPYABLE(EventLoop);
};

}  // namespace dkcoro
