/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "event_loop.h"

#include "ev_event_loop.h"
#include "uv_event_loop.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<event_loop> event_loop::create(const type type) {
  std::shared_ptr<event_loop> result;
  switch (type) {
    case type::EV:
      result = std::dynamic_pointer_cast<event_loop>(ev_event_loop::create());
      break;
    case type::UV:
      result = std::dynamic_pointer_cast<event_loop>(uv_event_loop::create());
      break;
    default:
      LOG(FATAL) << "unsupported provider: " << static_cast<uint32_t>(type);
      break;
  }
  return result;
}

}  // namespace dkcoro
