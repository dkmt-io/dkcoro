/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#include "ev_timer.h"

namespace dkcoro {  //

std::shared_ptr<ev_timer> ev_timer::create(const timer::options& options) {
  std::shared_ptr<ev_timer> timer(new ev_timer(options));
  return timer;
}

ev_timer::ev_timer(const timer::options& options) {}

bool ev_timer::start() {
  return false;
}

bool ev_timer::stop() {
  return false;
}

}  // namespace dkcoro
