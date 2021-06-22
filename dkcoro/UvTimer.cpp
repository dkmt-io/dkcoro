/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#include "UvTimer.h"

#include <glog/logging.h>

namespace dkcoro {  //

std::shared_ptr<UvTimer> UvTimer::Create(
  const Timer::Options& options, uv_loop_t* loop  //
) {
  std::shared_ptr<UvTimer> timer(new UvTimer(options, loop));
  return timer;
}

UvTimer::UvTimer(const Timer::Options& options, uv_loop_t* loop) :
  cb(options.cb),
  delay(options.delay),
  repeat(options.repeat),
  uvLoop(loop)  //
{
  CHECK_NOTNULL(uvLoop);
  int rc = uv_timer_init(uvLoop, &uvHandle.timer);
  CHECK(rc == 0);
  uvHandle.timer.data = this;
}

bool UvTimer::Start() {
  CHECK(self == nullptr);
  int rc = uv_timer_start(
    &uvHandle.timer,
    UvTimer::timerCb,
    delay,
    repeat ? delay : 0  //
  );
  CHECK(rc == 0);
  self = shared_from_this();
  return true;
}

bool UvTimer::Stop() {
  if (finished) {
    return true;
  }
  finished = true;
  int rc = uv_timer_stop(&uvHandle.timer);
  CHECK(rc == 0);
  if (!uv_is_closing(&uvHandle.handle)) {
    uv_close(&uvHandle.handle, UvTimer::closeCb);
  }
  return true;
}

void UvTimer::closeCb(uv_handle_t* handle) {
  auto* self = reinterpret_cast<UvTimer*>(handle->data);
  CHECK_NOTNULL(self);
  self->cb = nullptr;
  self->self = nullptr;
}

void UvTimer::timerCb(uv_timer_t* timer) {
  UvTimer* self = reinterpret_cast<UvTimer*>(timer->data);
  CHECK_NOTNULL(self);
  self->cb();
  if (!self->repeat) {
    self->Stop();
  }
}

}  // namespace dkcoro