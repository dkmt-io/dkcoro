/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "ev_event_loop.h"

#include "ev_timer.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<ev_event_loop> ev_event_loop::create() {
  std::shared_ptr<ev_event_loop> self(new ev_event_loop());
  return self;
}

ev_event_loop::ev_event_loop() {
  m_event_base = event_base_new();
  CHECK(m_event_base != nullptr);
}

ev_event_loop::~ev_event_loop() {
  event_base_free(m_event_base);
  m_event_base = nullptr;
}

void ev_event_loop::run() {
  event_base_dispatch(m_event_base);
}

std::shared_ptr<timer> ev_event_loop::set_timeout(
  const timer::callback& cb, uint64_t delay  //
) {
  auto timer = ev_timer::create(
    {.cb = cb, .delay = delay, .repeat = false}, m_event_base  //
  );
  bool success = timer->start();
  CHECK(success);
  return timer;
}

std::shared_ptr<timer> ev_event_loop::set_interval(
  const timer::callback& cb, uint64_t delay  //
) {
  auto timer = ev_timer::create(
    {.cb = cb, .delay = delay, .repeat = true}, m_event_base  //
  );
  bool success = timer->start();
  CHECK(success);
  return timer;
}

}  // namespace dkcoro
