/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#include "uv_timer.h"

#include <glog/logging.h>

namespace dkcoro {  //

std::shared_ptr<uv_timer> uv_timer::create(
  const timer::options& options, uv_loop_t* loop  //
) {
  std::shared_ptr<uv_timer> timer(new uv_timer(options, loop));
  return timer;
}

uv_timer::uv_timer(const timer::options& options, uv_loop_t* loop) :
  m_cb(options.cb),
  m_delay(options.delay),
  m_repeat(options.repeat)  //
{
  CHECK_NOTNULL(loop);
  int rc = uv_timer_init(loop, &m_uv_handle.timer);
  CHECK(rc == 0);
  m_uv_handle.timer.data = this;
}

bool uv_timer::start() {
  CHECK(m_self == nullptr);
  int rc = uv_timer_start(
    &m_uv_handle.timer,
    uv_timer::timer_cb,
    m_delay,
    m_repeat ? m_delay : 0  //
  );
  CHECK(rc == 0);
  m_self = shared_from_this();
  return true;
}

bool uv_timer::stop() {
  if (m_finished) {
    return true;
  }
  m_finished = true;
  int rc = uv_timer_stop(&m_uv_handle.timer);
  CHECK(rc == 0);
  if (!uv_is_closing(&m_uv_handle.handle)) {
    uv_close(&m_uv_handle.handle, uv_timer::close_cb);
  }
  return true;
}

void uv_timer::close_cb(uv_handle_t* handle) {
  auto* self = reinterpret_cast<dkcoro::uv_timer*>(handle->data);
  CHECK_NOTNULL(self);
  self->m_cb = nullptr;
  self->m_self = nullptr;
}

void uv_timer::timer_cb(uv_timer_t* timer) {
  auto* self = reinterpret_cast<dkcoro::uv_timer*>(timer->data);
  CHECK_NOTNULL(self);
  CHECK_NOTNULL(self->m_cb);
  self->m_cb();
  if (!self->m_repeat) {
    self->stop();
  }
}

}  // namespace dkcoro