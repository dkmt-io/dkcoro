/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "EventLoop.h"
#include "EvEventLoop.h"
#include "UvEventLoop.h"

namespace dkcoro {

static std::shared_ptr<EventLoop> Create() {
  return EvEventLoop::Create();
}

}  // namespace dkcoro
