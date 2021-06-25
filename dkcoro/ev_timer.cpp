/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#include "ev_timer.h"

#include <glog/logging.h>

#include <stdint.h>

namespace dkcoro {  //

namespace {

void ms_to_timeval(timeval& tv, int64_t ms) {
  evutil_timerclear(&tv);
  tv.tv_sec = ms / 1000;
  tv.tv_usec = (ms % 1000) * 1000;
}

}  // namespace

std::shared_ptr<ev_timer> ev_timer::create(
  const timer::options& options, event_base* base  //
) {
  std::shared_ptr<ev_timer> timer(new ev_timer(options, base));
  return timer;
}

ev_timer::ev_timer(const timer::options& options, event_base* base) :
  m_cb(options.cb),
  m_delay(options.delay),
  m_repeat(options.repeat)  //
{
  m_event = event_new(  //
    base,
    -1,
    m_repeat ? EV_PERSIST : 0,
    ev_timer::timeout_cb,
    this  //
  );
}

ev_timer::~ev_timer() {
  CHECK_NOTNULL(m_event);
  event_free(m_event);
  m_event = nullptr;
}

bool ev_timer::start() {
  CHECK(m_self == nullptr);
  timeval tv;
  ms_to_timeval(tv, m_delay);
  int rc = event_add(m_event, &tv);
  CHECK(rc == 0);
  m_self = shared_from_this();
  return true;
}

bool ev_timer::stop() {
  int rc = event_del(m_event);
  CHECK(rc == 0);
  m_cb = nullptr;
  m_self = nullptr;
  return true;
}

void ev_timer::timeout_cb(evutil_socket_t fd, short event, void* arg) {
  CHECK_NOTNULL(arg);
  ev_timer* timer = reinterpret_cast<ev_timer*>(arg);
  CHECK_NOTNULL(timer->m_cb);
  timer->m_cb();
  if (!timer->m_repeat) {
    timer->m_cb = nullptr;
    timer->stop();
  }
}

}  // namespace dkcoro
