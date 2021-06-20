/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "EvEventLoop.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<EvEventLoop> EvEventLoop::Create() {
  std::shared_ptr<EvEventLoop> self(new EvEventLoop());
  return self;
}

EvEventLoop::EvEventLoop() {
  eventBase = event_base_new();
  CHECK(eventBase != nullptr);
}

EvEventLoop::~EvEventLoop() {
  event_base_free(eventBase);
  eventBase = nullptr;
}

void EvEventLoop::Run() {
  event_base_dispatch(eventBase);
}

}  // namespace dkcoro
