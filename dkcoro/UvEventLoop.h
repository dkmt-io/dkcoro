/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include <memory>

#include "EventLoop.h"
#include "Uncopyable.h"

namespace dkcoro {

class UvEventLoop final : public EventLoop {
 public:
  static std::shared_ptr<UvEventLoop> Create();

  ~UvEventLoop();

  void Run();

 private:
  UvEventLoop();

  DK_DECLARE_UNCOPYABLE(UvEventLoop);
};

}  // namespace dkcoro
