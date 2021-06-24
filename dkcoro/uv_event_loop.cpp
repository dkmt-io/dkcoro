/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "uv_event_loop.h"
#include "uv_timer.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<uv_event_loop> uv_event_loop::create() {
  std::shared_ptr<uv_event_loop> self(new uv_event_loop());
  return self;
}

uv_event_loop::uv_event_loop() {
  int rc = uv_loop_init(&m_uv_loop);
  CHECK(rc == 0);
}

uv_event_loop::~uv_event_loop() {
  int rc = uv_loop_close(&m_uv_loop);
  CHECK(rc == 0);
}

void uv_event_loop::run() {
  int rc = uv_run(&m_uv_loop, UV_RUN_DEFAULT);
  CHECK(rc == 0);
}

std::shared_ptr<timer> uv_event_loop::set_timeout(
  const timer::callback& cb, uint64_t delay  //
) {
  auto timer = uv_timer::create(
    {.cb = cb, .delay = delay, .repeat = false}, &m_uv_loop  //
  );
  bool success = timer->start();
  CHECK(success);
  return timer;
}

std::shared_ptr<timer> uv_event_loop::set_interval(
  const timer::callback& cb, uint64_t delay  //
) {
  auto timer = uv_timer::create(
    {.cb = cb, .delay = delay, .repeat = true}, &m_uv_loop  //
  );
  bool success = timer->start();
  CHECK(success);
  return timer;
}

}  // namespace dkcoro
