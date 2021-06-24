/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "dkcoro/async_awaiter.h"
#include "dkcoro/coro_return.h"
#include "dkcoro/delay.h"
#include "dkcoro/event_loop.h"
#include "dkcoro/utils.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

#include <stdlib.h>
#include <iostream>
#include <memory>

dkcoro::coro_return<> coro_main(std::shared_ptr<dkcoro::event_loop> loop) {
  for (int i = 0; i < 10; i++) {
    LOG(INFO) << "heartbeat #" << i;
    co_await loop->delay(1000);
  }
  co_return;
}

int main(int argc, char** argv) {
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
  GFLAGS_NAMESPACE::SetCommandLineOption("logtostderr", "true");
  google::InitGoogleLogging(argv[0]);
  auto loop = dkcoro::event_loop::create();
  coro_main(loop);
  loop->run();
  return EXIT_SUCCESS;
}
