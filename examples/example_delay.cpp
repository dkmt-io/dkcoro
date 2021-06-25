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

DEFINE_int32(event_loop_type, 1, "event loop type. 1: libevent, 2: libuv.");

dkcoro::coro_return<> coro_main(std::shared_ptr<dkcoro::event_loop> loop) {
  for (int i = 0; i < 10; i++) {
    LOG(INFO) << "heartbeat #" << i;
    co_await loop->delay(1000);
  }
  co_return;
}

int main(int argc, char** argv) {
  using dkcoro::event_loop;
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
  GFLAGS_NAMESPACE::SetCommandLineOption("logtostderr", "true");
  google::InitGoogleLogging(argv[0]);
  std::shared_ptr<event_loop> loop;
  switch (FLAGS_event_loop_type) {
    case 1:  // libevent
      loop = event_loop::create(event_loop::type::EV);
      LOG(INFO) << "using libevent";
      break;
    case 2:  // libuv
      loop = event_loop::create(event_loop::type::UV);
      LOG(INFO) << "using libuv";
      break;
    default:
      LOG(ERROR) << "invalid event loop type " << FLAGS_event_loop_type;
      return EXIT_FAILURE;
      break;
  }
  coro_main(loop);
  loop->run();
  return EXIT_SUCCESS;
}
