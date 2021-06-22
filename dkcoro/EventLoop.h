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
  enum class ProviderType : uint8_t {
    EV = 1,
    UV = 2,
  };

  static std::shared_ptr<EventLoop> Create(
    const ProviderType type = ProviderType::UV  //
  );

  virtual void Run() = 0;

 protected:
  EventLoop() {}

  DK_DECLARE_UNCOPYABLE(EventLoop);
};

}  // namespace dkcoro
