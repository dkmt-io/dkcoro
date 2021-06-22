/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "UvEventLoop.h"
#include "UvTimer.h"

#include <glog/logging.h>

namespace dkcoro {

std::shared_ptr<UvEventLoop> UvEventLoop::Create() {
  std::shared_ptr<UvEventLoop> self(new UvEventLoop());
  return self;
}

UvEventLoop::UvEventLoop() {
  int rc = uv_loop_init(&uvLoop);
  CHECK(rc == 0);
}

UvEventLoop::~UvEventLoop() {
  int rc = uv_loop_close(&uvLoop);
  CHECK(rc == 0);
}

void UvEventLoop::Run() {
  int rc = uv_run(&uvLoop, UV_RUN_DEFAULT);
  CHECK(rc == 0);
}

std::shared_ptr<Timer> UvEventLoop::SetTimeout(
  const Timer::Callback& cb, uint64_t delay  //
) {
  auto timer = UvTimer::Create(
    {.cb = cb, .delay = delay, .repeat = false}, &uvLoop  //
  );
  bool success = timer->Start();
  CHECK(success);
  return timer;
}

std::shared_ptr<Timer> UvEventLoop::SetInterval(
  const Timer::Callback& cb, uint64_t delay  //
) {
  auto timer = UvTimer::Create(
    {.cb = cb, .delay = delay, .repeat = true}, &uvLoop  //
  );
  bool success = timer->Start();
  CHECK(success);
  return timer;
}

}  // namespace dkcoro
