/**
 * @author hans@dkmt.io
 * @date 2021-06-22
 */

#include "dkcoro/EventLoop.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

TEST(EventLoopTest, EvTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::EV);
  loop->Run();
}

TEST(EventLoopTest, UvTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::UV);
  loop->Run();
}

TEST(EventLoopTest, UvSetTimeoutTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::UV);
  LOG(INFO) << "timer begin";
  loop->SetTimeout([]() { LOG(INFO) << "timer end"; }, 100);
  loop->Run();
}

TEST(EventLoopTest, UvSetIntervalTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::UV);
  LOG(INFO) << "timer begin";
  int counter = 0;
  std::shared_ptr<dkcoro::Timer> timer;
  timer = loop->SetInterval(
    [&counter, &timer]() {
      counter++;
      LOG(INFO) << "timer fired " << counter;
      if (counter >= 5) {
        timer->Stop();
      }
    },
    100  //
  );
  loop->Run();
}
