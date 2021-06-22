/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "EventLoop.h"
#include "EvEventLoop.h"
#include "UvEventLoop.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<EventLoop> EventLoop::Create(const ProviderType type) {
  std::shared_ptr<EventLoop> result;
  switch (type) {
    case ProviderType::EV:
      result = std::dynamic_pointer_cast<EventLoop>(EvEventLoop::Create());
      break;
    case ProviderType::UV:
      result = std::dynamic_pointer_cast<EventLoop>(UvEventLoop::Create());
      break;
    default:
      LOG(FATAL) << "unsupported provider: " << static_cast<uint32_t>(type);
      break;
  }
  return result;
}

}  // namespace dkcoro
