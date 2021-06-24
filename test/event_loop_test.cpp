/**
 * @author hans@dkmt.io
 * @date 2021-06-22
 */

#include "dkcoro/event_loop.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

TEST(event_loop_test, ev_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::EV);
  loop->run();
}

TEST(event_loop_test, uv_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  loop->run();
}

TEST(event_loop_test, uv_set_timeout_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  LOG(INFO) << "timer begin";
  loop->set_timeout([]() { LOG(INFO) << "timer end"; }, 100);
  loop->run();
}

TEST(event_loop_test, uv_set_interval_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  LOG(INFO) << "timer begin";
  int counter = 0;
  std::shared_ptr<dkcoro::timer> timer;
  timer = loop->set_interval(
    [&counter, &timer]() {
      counter++;
      LOG(INFO) << "timer fired " << counter;
      if (counter >= 5) {
        timer->stop();
      }
    },
    100  //
  );
  loop->run();
}
