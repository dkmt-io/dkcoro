/**
 * @author hans@dkmt.io
 * @date 2021-06-22
 */

#include "dkcoro/event_loop.h"
#include "dkcoro/utils.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <math.h>

dkcoro::coro_return<> set_timeout_test(
  std::shared_ptr<dkcoro::event_loop> loop  //
) {
  auto t0 = dkcoro::utils::now();
  LOG(INFO) << "timer begin at: " << t0;
  auto counter = 0;
  loop->set_timeout(
    [t0, &counter]() {
      auto t1 = dkcoro::utils::now();
      LOG(INFO) << "timer end at: " << t1;
      auto duration = t1 - t0;
      auto diff = abs(duration - 100);
      LOG(INFO) << "diff " << diff;
      EXPECT_TRUE(diff <= 10);
      counter++;
    },
    100  //
  );
  loop->run();
  EXPECT_EQ(1, counter);
  co_return;
}

dkcoro::coro_return<> set_interval_test(
  std::shared_ptr<dkcoro::event_loop> loop  //
) {
  LOG(INFO) << "timer begin";
  int counter = 0;
  std::shared_ptr<dkcoro::timer> timer;
  auto t0 = dkcoro::utils::now();
  timer = loop->set_interval(
    [&counter, &timer, &t0]() {
      auto t1 = dkcoro::utils::now();
      auto duration = t1 - t0;
      auto diff = abs(duration - 100);
      LOG(INFO) << "diff " << diff;
      EXPECT_TRUE(diff <= 10);
      t0 = t1;
      counter++;
      LOG(INFO) << "timer fired " << counter;
      if (counter >= 5) {
        timer->stop();
      }
    },
    100  //
  );
  loop->run();
  EXPECT_EQ(5, counter);
  co_return;
}

dkcoro::coro_return<> delay_test(std::shared_ptr<dkcoro::event_loop> loop) {
  auto t0 = dkcoro::utils::now();
  for (int i = 0; i < 10; i++) {
    LOG(INFO) << "heartbeat #" << i;
    co_await loop->delay(100);
    auto t1 = dkcoro::utils::now();
    auto duration = t1 - t0;
    auto diff = abs(duration - 100);
    LOG(INFO) << "diff " << diff;
    EXPECT_TRUE(diff <= 10);
    t0 = t1;
  }
  co_return;
};

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

TEST(event_loop_test, ev_set_timeout_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::EV);
  set_timeout_test(loop);
}

TEST(event_loop_test, uv_set_timeout_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  set_timeout_test(loop);
}

TEST(event_loop_test, ev_set_interval_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::EV);
  set_interval_test(loop);
}

TEST(event_loop_test, uv_set_interval_test) {
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  set_interval_test(loop);
}

TEST(event_loop_test, ev_delay_test) {
  using dkcoro::coro_return;
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::EV);
  delay_test(loop);
  loop->run();
}

TEST(event_loop_test, uv_delay_test) {
  using dkcoro::coro_return;
  using dkcoro::event_loop;
  auto loop = event_loop::create(event_loop::type::UV);
  delay_test(loop);
  loop->run();
}
